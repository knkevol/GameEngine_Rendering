#include "Precompiled.h"

#define WGL_CONTEXT_MAJOR_VERSION_ARB 0x2091
#define WGL_CONTEXT_MINOR_VERSION_ARB 0x2092
#define WGL_CONTEXT_PROFILE_MASK_ARB 0x9126
#define WGL_CONTEXT_CORE_PROFILE_BIT_ARB 0x00000001

typedef HGLRC(WINAPI* PFNWGLCREATECONTEXTATTRIBSARBPROC)(HDC hDC, HGLRC hShareContext, const int* attribList);
typedef BOOL(WINAPI* PFNWGLSWAPINTERVALEXTPROC)(int interval);


WindowsGLContext::~WindowsGLContext()
{
	Shutdown();
}

// HWND -> HDC
bool WindowsGLContext::Init(HWND InHandle)
{
	_Handle = InHandle;
	_DeviceContext = ::GetDC(_Handle); // 그냥 GetDC와 차이
	if (!_DeviceContext)
	{
		return false;
	}

	if (!SetupPixelFormat())
	{
		return false;
	}

	// 더미 Context -> Core3.3 Context
	if (!CreateModernContext())
	{
		return false;
	}

	if (!wglMakeCurrent(_DeviceContext, _RenderContext))
	{
		return false;
	}

	if (!gladLoadGL())
	{
		return false;
	}

	glEnable(GL_DEPTH_TEST);

	//VSync 설정
	PFNWGLSWAPINTERVALEXTPROC wglSwapIntervalEXT = (PFNWGLSWAPINTERVALEXTPROC)wglGetProcAddress("wglSwapIntervalEXT");

	if (wglSwapIntervalEXT)
	{
		wglSwapIntervalEXT(1);
	}


	return true;
}

void WindowsGLContext::Shutdown()
{
	if (_RenderContext)
	{
		wglMakeCurrent(nullptr, nullptr);
		wglDeleteContext(_RenderContext);
		_RenderContext = nullptr;
	}

	if (_DeviceContext)
	{
		ReleaseDC(_Handle, _DeviceContext);
		_DeviceContext = nullptr;
	}
}

void WindowsGLContext::Clear(float InR, float InG, float InB, float InA)
{
	glClearColor(InR, InG, InB, InA);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void WindowsGLContext::SwapBuffers()
{
	::SwapBuffers(_DeviceContext);
}

void WindowsGLContext::OnResize(int InWidth, int InHeight)
{
	glViewport(0, 0, InWidth, InHeight);
}

bool WindowsGLContext::SetupPixelFormat()
{

	PIXELFORMATDESCRIPTOR pfd = {};
	pfd.nSize = sizeof(PIXELFORMATDESCRIPTOR);
	pfd.nVersion = 1;
	pfd.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
	pfd.iPixelType = PFD_TYPE_RGBA;
	pfd.cColorBits = 32;
	pfd.cDepthBits = 24;
	pfd.cStencilBits = 8;
	pfd.iLayerType = PFD_MAIN_PLANE;

	int pixelFormat = ChoosePixelFormat(_DeviceContext, &pfd);
	if (pixelFormat == 0)
	{
		return false;
	}

	return SetPixelFormat(_DeviceContext, pixelFormat, &pfd) == TRUE;
}

bool WindowsGLContext::CreateModernContext()
{
	HGLRC dummyContext = wglCreateContext(_DeviceContext);
	if (!dummyContext)
	{
		return false;
	}
	wglMakeCurrent(_DeviceContext, dummyContext); //GPU Driver Connect

	PFNWGLCREATECONTEXTATTRIBSARBPROC wglCreateContextAttribsARB = (PFNWGLCREATECONTEXTATTRIBSARBPROC)wglGetProcAddress("wglCreateContextAttribsARB");

	if (!wglCreateContextAttribsARB)
	{
		wglMakeCurrent(nullptr, nullptr);
		wglDeleteContext(dummyContext);
		return false;
	}

	int attribs[] = {
		WGL_CONTEXT_MAJOR_VERSION_ARB, 3,
		WGL_CONTEXT_MINOR_VERSION_ARB, 3,
		WGL_CONTEXT_PROFILE_MASK_ARB, 
		WGL_CONTEXT_CORE_PROFILE_BIT_ARB,
		0
	};

	_RenderContext = wglCreateContextAttribsARB(_DeviceContext, nullptr, attribs);

	wglMakeCurrent(nullptr, nullptr);
	wglDeleteContext(dummyContext);


	return _RenderContext != nullptr;
}
