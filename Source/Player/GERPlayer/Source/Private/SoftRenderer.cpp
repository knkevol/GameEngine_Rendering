#include "Precompiled.h"
#include "SoftRenderer.h"

using namespace GER::DDD;

SoftRenderer::SoftRenderer(RendererInterface* InRSI) : _RSIPtr(InRSI)
{
}

void SoftRenderer::OnInit()
{
	// GLContext가 준비된 직후 1회만 셰이더 컴파일 진행
	OpenGLDevice& device = static_cast<OpenGLRSI&>(GetRenderer()).GetDevice();

	std::string vsSrc = LoadShaderSource("Source/Runtime/Renderer/Shaders/basic.vert");
	std::string fsSrc = LoadShaderSource("Source/Runtime/Renderer/Shaders/basic.frag");
	std::string skinnedVsSrc = LoadShaderSource("Source/Runtime/Renderer/Shaders/skinned.vert");
	std::string depthFsSrc = LoadShaderSource("Source/Runtime/Renderer/Shaders/depth.frag");

	_StaticShader = device.CreateShaderProgram(vsSrc.c_str(), fsSrc.c_str());
	_SkinnedShader = device.CreateShaderProgram(skinnedVsSrc.c_str(), fsSrc.c_str());
	_StaticDepthShader = device.CreateShaderProgram(vsSrc.c_str(), depthFsSrc.c_str());
	_SkinnedDepthShader = device.CreateShaderProgram(skinnedVsSrc.c_str(), depthFsSrc.c_str());

	// binding point 0 = camera, 1 = light
	_CameraUBO = device.CreateUniformBuffer(sizeof(CameraUBOData), 0);
	_LightUBO = device.CreateUniformBuffer(sizeof(LightUBOData), 1);

	device.BindUniformBlock(_StaticShader, "CameraBlock", 0);
	device.BindUniformBlock(_SkinnedShader, "CameraBlock", 0);
	device.BindUniformBlock(_StaticDepthShader, "CameraBlock", 0);
	device.BindUniformBlock(_SkinnedDepthShader, "CameraBlock", 0);

	device.BindUniformBlock(_StaticShader, "LightBlock", 1);
	device.BindUniformBlock(_SkinnedShader, "LightBlock", 1);

	// Skybox
	std::string skyboxVsSrc = LoadShaderSource("Source/Runtime/Renderer/Shaders/skybox.vert");
	std::string skyboxFsSrc = LoadShaderSource("Source/Runtime/Renderer/Shaders/skybox.frag");
	_SkyboxShader = device.CreateShaderProgram(skyboxVsSrc.c_str(), skyboxFsSrc.c_str());
	device.BindUniformBlock(_SkyboxShader, "CameraBlock", 0);

	_SkyboxMesh = device.CreateSkyboxMesh();

	_Skybox.LoadFromFolder("Asset/Skybox/Sky");
	_Skybox.UploadToGPU(device);

	// ShadowMap
	std::string shadowVsSrc = LoadShaderSource("Source/Runtime/Renderer/Shaders/shadow_depth.vert");
	std::string shadowSkinnedVsSrc = LoadShaderSource("Source/Runtime/Renderer/Shaders/shadow_depth_skinned.vert");
	std::string shadowFsSrc = LoadShaderSource("Source/Runtime/Renderer/Shaders/shadow_depth.frag");

	_ShadowDepthStaticShader = device.CreateShaderProgram(shadowVsSrc.c_str(), shadowFsSrc.c_str());
	_ShadowDepthSkinnedShader = device.CreateShaderProgram(shadowSkinnedVsSrc.c_str(), shadowFsSrc.c_str());

	_ShadowMap = device.CreateShadowMap(ShadowMapResolution, ShadowMapResolution);

	// Postprcess
	std::string postVsSrc = LoadShaderSource("Source/Runtime/Renderer/Shaders/postprocess.vert");
	std::string postFsSrc = LoadShaderSource("Source/Runtime/Renderer/Shaders/postprocess.frag");
	_PostProcessShader = device.CreateShaderProgram(postVsSrc.c_str(), postFsSrc.c_str());

	_FullScreenQuadMesh = device.CreateFullScreenQuadMesh();
	_SceneFrameBuffer = device.CreateSceneFrameBuffer((UINT32)_ScreenSize.X, (UINT32)_ScreenSize.Y);

	//
	SetupDefaultLights();

	SetBackgroundColor(LinearColor(0.15f, 0.15f, 0.2f, 1.0f));

	::MessageBox(nullptr, "Begin to Tick", "SoftRenderer Init Finished", MB_OK);
}

void SoftRenderer::OnTick()
{
	if (!_AllInitialized)
	{
		InitSubsystems();
		return;
	}

	// Check Condition + TickEnabled
	assert(_RSIPtr != nullptr && GetRenderer().IsInitialized() && !_ScreenSize.HasZero());

	if (_TickEnabled)
	{
		PreUpdate();
		Update(_FrameTime / 1000.0f);
		LateUpdate(_FrameTime / 1000.0f);

		Render();
		PostRender();
	}
}

void SoftRenderer::OnResize(const ScreenPoint& InNewScreenSize)
{
	_ScreenSize = InNewScreenSize;

	if (_RendererInitialized)
	{
		GetRenderer().Init(_ScreenSize);
	}

	if (_GameEngineInitialized)
	{
		GetGameEngine().OnScreenResize(_ScreenSize);
	}
}

void SoftRenderer::OnShutdown()
{
	GetRenderer().Shutdown();
}

bool SoftRenderer::InitSubsystems()
{
	// Check Screen Size
	if (_ScreenSize.HasZero())
	{
		::MessageBox(nullptr, "ScreenSize HasZero", "Error", MB_OK);
		return false;
	}

	// Init Performance counter
	if (!_PerformanceCheckInitialized)
	{
		if (_PerformanceInitFunc && _PerformanceMeasureFunc)
		{
			_CyclesPerMilliSeconds = _PerformanceInitFunc();
			_PerformanceCheckInitialized = true;
		}
		else
		{
			assert(false);
			return false;
		}
	}

	if (!_RendererInitialized)
	{
		_RendererInitialized = GetRenderer().Init(_ScreenSize);
		if (!_RendererInitialized)
		{
			assert(false);
			return false;
		}
	}

	_GameEngineInitialized = GetGameEngine().IsInitialized();
	if (!_GameEngineInitialized)
	{
		GetGameEngine().OnScreenResize(_ScreenSize);
		InputManager& input = GetGameEngine().GetInputManager();
		if (!input.IsInputReady())
		{
			_InputBindingFunc(input);
		}

		_GameEngineInitialized = GetGameEngine().Init();
		if (!_GameEngineInitialized)
		{
			assert(false);
			return false;
		}

		LoadScene();
	}

	_AllInitialized = _PerformanceCheckInitialized && _RendererInitialized && _GameEngineInitialized;

	if (_AllInitialized)
	{
		_TickEnabled = true;
		OnInit();
	}

	return _TickEnabled;
}

void SoftRenderer::PreUpdate()
{
	// Performance Check
	_FrameTimeStamp = _PerformanceMeasureFunc();
	if (_FrameCount == 0)
	{
		_StartTimeStamp = _FrameTimeStamp;
	}

	GetRenderer().Clear(_BackgroundColor);

	const SystemInputManager& sinput = GetSystemInput();

	if (sinput.IsReleased(SystemInputButton::F1)) { SetDrawMode(DrawMode::Normal); }
	if (sinput.IsReleased(SystemInputButton::F2)) { SetDrawMode(DrawMode::Wireframe); }
	if (sinput.IsReleased(SystemInputButton::F3)) { SetDrawMode(DrawMode::OnlyBone); }
	if (sinput.IsReleased(SystemInputButton::F4)) { TestTempLog(); }
	if (sinput.IsReleased(SystemInputButton::F5)) { SetDrawMode(DrawMode::DepthBuffer); } // GPU
	if (sinput.IsReleased(SystemInputButton::F6)) { SetEnvReflectionEnabled(!IsEnvReflectionEnabled()); }
	if (sinput.IsReleased(SystemInputButton::F7)) { TestPermLog(); }
	if (sinput.IsReleased(SystemInputButton::F9)) { TestFunc(); }
}

void SoftRenderer::Update(float InDeltaSeconds)
{
	GameEngine& g = GetDirectGameEngine();
	const InputManager& input = g.GetInputManager();


	float CameraRotateSpeed = 90.0f;
	float CameraMoveSpeed = 200.0f;

	CameraObject& camera = g.GetMainCamera();

	// TODO - Temp first position
	static bool firstUpdate = true;
	if (firstUpdate)
	{
		camera.GetTransform().SetWorldPosition(Vector3(3.f, -195.f, 84.f));
		camera.GetTransform().SetWorldRotation(Rotator(55.f, 125.f, -89.f));
		firstUpdate = false;
	}

	// TODO - Improve Camera Rotation
	camera.GetTransform().AddLocalYawRotation(input.GetAxis(InputAxis::XAxis) * CameraRotateSpeed * InDeltaSeconds);
	camera.GetTransform().AddLocalPitchRotation(-input.GetAxis(InputAxis::YAxis) * CameraRotateSpeed * InDeltaSeconds);
	Vector3 CameraMovement(input.GetAxis(InputAxis::X2Axis) * CameraMoveSpeed * InDeltaSeconds, input.GetAxis(InputAxis::Y2Axis) * CameraMoveSpeed * InDeltaSeconds, -input.GetAxis(InputAxis::Z2Axis) * CameraMoveSpeed * InDeltaSeconds);
	camera.GetTransform().AddWorldPosition(CameraMovement);

	if (input.IsReleased(InputButton::Z))
	{
		// TODO - Do Something
		auto& g = GetGameEngine();
		auto& l = g.GetLogs()[0];
		l.PushLog("Input :: Z", 5000.0f);
		//g.InterfaceTestFunction();		
	}
}

void SoftRenderer::PostRender()
{
	GetRenderer().EndFrame();

	// 입력 상태 업데이트
	GetGameEngine().GetInputManager().UpdateInput();
	GetSystemInput().UpdateSystemInput();

	// 성능 측정 마무리.
	_FrameCount++;
	INT64 currentTimeStamp = _PerformanceMeasureFunc();
	INT64 frameCycles = currentTimeStamp - _FrameTimeStamp;
	INT64 elapsedCycles = currentTimeStamp - _StartTimeStamp;
	_FrameTime = frameCycles / _CyclesPerMilliSeconds;
	_ElapsedTime = elapsedCycles / _CyclesPerMilliSeconds;
	_FrameFPS = _FrameTime == 0.f ? 0.f : 1000.f / _FrameTime;
	_AverageFPS = _ElapsedTime == 0.f ? 0.f : 1000.f / _ElapsedTime * _FrameCount;
}

void SoftRenderer::PushLog(const std::string& LogString)
{
	auto& g = GetGameEngine();
	auto& l = g.GetLogs()[0];

	l.PushLog(LogString, 5000.0f);
}

void SoftRenderer::PushLog(const std::string& LogHeader, const std::string& LogString)
{
	auto& g = GetGameEngine();
	auto& l = g.GetTargetLog(LogString);

	l.PushLog(LogString, 5000.0f);
}

void SoftRenderer::PushLog(const std::string& LogHeader, const std::string& LogString, bool IsOnScreen)
{
	auto& g = GetGameEngine();
	auto& l = g.GetTargetLog(LogString);

	l.PushLog(LogString, IsOnScreen);
}

void SoftRenderer::PushLog(const std::string& LogHeader, const std::string& LogString, float LifeTime)
{
	auto& g = GetGameEngine();
	auto& l = g.GetTargetLog(LogHeader);

	l.PushLog(LogString, LifeTime);
}

