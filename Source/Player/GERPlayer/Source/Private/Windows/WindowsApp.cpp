#include "Precompiled.h"
#include "SoftRenderer.h"
#include "WindowsUtil.h"
#include "WindowsPlayer.h"
#include "WindowsGLContext.h"

using namespace GER::DDD;

int CALLBACK WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nCmdShow)
{
	ScreenPoint defScreenSize(800, 600);
	SoftRenderer instance(new WindowsRSI());

	WindowsGLContext glContext;

	WindowsPlayer::gOnResizeFunc = [&instance, &glContext](const ScreenPoint& InNewScreenSize) {
		if (InNewScreenSize.HasZero()) {
			return;
		}
		instance.OnResize(InNewScreenSize);
		glContext.OnResize(InNewScreenSize.X, InNewScreenSize.Y);
	};

	instance._PerformanceInitFunc = WindowsUtil::GetCyclesPerMilliSeconds;
	instance._PerformanceMeasureFunc = WindowsUtil::GetCurrentTimeStamp;
	instance._InputBindingFunc = WindowsUtil::BindInput;
	WindowsUtil::BindSystemInput(instance.GetSystemInput());

	if (!WindowsPlayer::Create(hInstance, defScreenSize))
	{
		return -1;
	}

	if (!glContext.Init(WindowsPlayer::gHandle))
	{
		MessageBox(nullptr, "OpenGL Context Creation Fail", "Error", MB_ICONEXCLAMATION | MB_OK);
		return -1;
	}

	//----------
	OpenGLDevice glDevice;

	std::string vsSrc = LoadShaderSource("Source/Runtime/Renderer/Shaders/basic.vert");
	std::string fsSrc = LoadShaderSource("Source/Runtime/Renderer/Shaders/basic.frag");
	ShaderHandle testShader = glDevice.CreateShaderProgram(vsSrc.c_str(), fsSrc.c_str());


	std::string skinnedVsSrc = LoadShaderSource("Source/Runtime/Renderer/Shaders/skinned.vert");
	ShaderHandle skinnedShader = glDevice.CreateShaderProgram(skinnedVsSrc.c_str(), fsSrc.c_str());

	std::string depthFsSrc = LoadShaderSource("Source/Runtime/Renderer/Shaders/depth.frag");
	ShaderHandle depthShader = glDevice.CreateShaderProgram(vsSrc.c_str(), depthFsSrc.c_str());
	ShaderHandle skinnedDepthShader = glDevice.CreateShaderProgram(skinnedVsSrc.c_str(), depthFsSrc.c_str());


	//---------

	WindowsUtil::Show(WindowsPlayer::gHandle);
	WindowsUtil::CenterWindow(WindowsPlayer::gHandle);

	static float previousTimer = 0.f;
	static float updatePeriod = 500.f;
	
	while (WindowsPlayer::Tick())
	{
		instance.OnTick();

		glContext.Clear(0.15f, 0.15f, 0.2f, 1.0f);
		
		if (instance.GetDirectGameEngine().IsInitialized())
		{
			instance.RenderWorldGPU(glDevice, testShader, skinnedShader, depthShader, skinnedDepthShader);

		}
		glContext.SwapBuffers();

		float currentTime = instance.GetElapsedTime();
		if (currentTime - previousTimer > updatePeriod)
		{
			float frameFPS = instance.GetFrameFPS();
			WindowsPlayer::SetWindowsStatTitle(frameFPS);
			previousTimer = currentTime;
		}
	}

	glContext.Shutdown();
	instance.OnShutdown();
	WindowsPlayer::Destroy();
	return 0;
}