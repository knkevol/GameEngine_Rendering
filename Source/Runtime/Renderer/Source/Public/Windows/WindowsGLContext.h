#pragma once

namespace GER
{

	class WindowsGLContext
	{
	public:
		WindowsGLContext() = default;
		~WindowsGLContext();

	public:
		bool Init(HWND InHandle);
		void Shutdown();

		void Clear(float InR, float InG, float InB, float InA);
		void SwapBuffers();
		void OnResize(int InWidth, int InHeight);

	private:
		bool SetupPixelFormat();
		bool CreateModernContext();

	private:
		HWND _Handle = nullptr;
		HDC _DeviceContext = nullptr;
		HGLRC _RenderContext = nullptr;

	};
}