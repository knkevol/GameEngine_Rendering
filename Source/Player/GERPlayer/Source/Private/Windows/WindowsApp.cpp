#include "Precompiled.h"
#include "SoftRenderer.h"
#include "WindowsUtil.h"
#include "WindowsPlayer.h"
#include "WindowsGLContext.h"

//test
using namespace GER::DDD;

static const char* TestVertexShaderSrc = R"(
#version 330 core
layout(location=0) in vec4 aPosition;
layout(location=1) in vec4 aColor;
out vec4 vColor;
void main()
{
	gl_Position = aPosition;
	vColor = aColor;
}
)";

static const char* TestFragmentShaderSrc = R"(
#version 330 core
in vec4 vColor;
out vec4 FragColor;
void main()
{
	FragColor = vColor;
}
)";

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

	Vertex3D triangleVertices[3] = {
		Vertex3D(Vector4(0.0f, 0.5f, 0.0f, 1.0f), LinearColor::Red),
		Vertex3D(Vector4(0.5f, -0.5f, 0.0f, 1.0f), LinearColor::Green),
		Vertex3D(Vector4(-0.5f, -0.5f, 0.0f, 1.0f), LinearColor::Blue),
	};
	UINT32 triangleIndices[3] = { 0, 1, 2 };

	GPUMeshHandle triangleMesh = glDevice.CreateMesh(triangleVertices, sizeof(triangleVertices), triangleIndices, 3);
	ShaderHandle testShader = glDevice.CreateShaderProgram(TestVertexShaderSrc, TestFragmentShaderSrc);
	//---------

	WindowsUtil::Show(WindowsPlayer::gHandle);
	WindowsUtil::CenterWindow(WindowsPlayer::gHandle);

	static float previousTimer = 0.f;
	static float updatePeriod = 500.f;
	
	while (WindowsPlayer::Tick())
	{
		instance.OnTick();

		glContext.Clear(0.15f, 0.15f, 0.2f, 1.0f);
		
		
		glDevice.UseShader(testShader);
		glDevice.BindMesh(triangleMesh);
		glDevice.DrawIndexed(3);

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