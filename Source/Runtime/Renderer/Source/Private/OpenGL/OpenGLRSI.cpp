#include "Precompiled.h"

OpenGLRSI::~OpenGLRSI()
{
	Shutdown();
}

bool OpenGLRSI::Init(const ScreenPoint& InScreenSize)
{
	HWND handle = ::GetActiveWindow();
	if (handle == nullptr)
	{
		return false;
	}

	if (!_GLContext.Init(handle))
	{
		return false;
	}

	_ScreenSize = InScreenSize;
	_Initialized = true;
	
	return true;
}

void GER::OpenGLRSI::Shutdown()
{
	_GLContext.Shutdown();
	_Initialized = false;
}

void GER::OpenGLRSI::Clear(const LinearColor& InClearColor)
{
	_GLContext.Clear(InClearColor.R, InClearColor.G, InClearColor.B, InClearColor.A);
}

void GER::OpenGLRSI::BeginFrame()
{
}

void GER::OpenGLRSI::EndFrame()
{
	_GLContext.SwapBuffers();
}

void GER::OpenGLRSI::DrawPoint(const Vector2& InVectorPos, const LinearColor& InColor)
{
}

void GER::OpenGLRSI::DrawPoint(const ScreenPoint& InScreenPos, const LinearColor& InColor)
{
}

void GER::OpenGLRSI::DrawLine(const Vector2& InStartPos, const Vector2& InEndPos, const LinearColor& InColor)
{
}

void GER::OpenGLRSI::DrawLine(const Vector4& InStartPos, const Vector4& InEndPos, const LinearColor& InColor)
{
}

float GER::OpenGLRSI::GetDepthBufferValue(const ScreenPoint& InPos) const
{
	return 0.0f;
}

void GER::OpenGLRSI::SetDepthBufferValue(const ScreenPoint& InPos, float InDepthValue)
{
}

void GER::OpenGLRSI::DrawFullVerticalLine(int InX, const LinearColor& InColor)
{
}

void GER::OpenGLRSI::DrawFullHorizontalLine(int InY, const LinearColor& InColor)
{
}

void GER::OpenGLRSI::PushStatisticText(std::string&& InText)
{
}

void GER::OpenGLRSI::PushStatisticTexts(std::vector<std::string>&& InTexts)
{
}

void GER::OpenGLRSI::PushLogText(std::string&& InText)
{
}

void GER::OpenGLRSI::PushLogTexts(std::vector<std::string>&& InTexts)
{
}

void GER::OpenGLRSI::PushLogText(std::size_t& Hash, std::string&& InText)
{
}

void GER::OpenGLRSI::PushLogTexts(std::vector<std::pair<std::size_t, std::string>>& NewLogs)
{
}

void GER::OpenGLRSI::DeleteLogText(std::size_t& HashToDelete)
{
}

void GER::OpenGLRSI::DeleteLogTexts(std::vector<std::size_t>& HashesToDelete)
{
}
