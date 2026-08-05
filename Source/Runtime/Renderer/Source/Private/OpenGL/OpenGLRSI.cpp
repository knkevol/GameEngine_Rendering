#include "Precompiled.h"

using namespace GER::DDD;

OpenGLRSI::~OpenGLRSI()
{
	Shutdown();
}

bool OpenGLRSI::Init(const ScreenPoint& InScreenSize)
{
	_ScreenSize = InScreenSize;

	if (_Initialized)
	{
		_GLContext.OnResize(InScreenSize.X, InScreenSize.Y);
		return true;
	}

	HWND handle = ::GetActiveWindow();
	if (handle == nullptr)
	{
		return false;
	}

	if (!_GLContext.Init(handle))
	{
		return false;
	}

	if (_OverlayShader == 0)
	{
		std::string overlayVs = LoadShaderSource("Source/Runtime/Renderer/Shaders/overlay.vert");
		std::string overlayFs = LoadShaderSource("Source/Runtime/Renderer/Shaders/overlay.frag");
		_OverlayShader = _Device.CreateShaderProgram(overlayVs.c_str(), overlayFs.c_str());
		_OverlayMesh = _Device.CreateOverlayMesh(_MaxOverlayQuads);

	}

	_Initialized = true;	
	return true;
}

void OpenGLRSI::Shutdown()
{
	_GLContext.Shutdown();
	_Initialized = false;
}

void OpenGLRSI::Clear(const LinearColor& InClearColor)
{
	_GLContext.Clear(InClearColor.R, InClearColor.G, InClearColor.B, InClearColor.A);
}

void OpenGLRSI::BeginFrame()
{
}

void OpenGLRSI::EndFrame()
{
	DrawOverlayTexts();
	_GLContext.SwapBuffers();
}

void OpenGLRSI::DrawPoint(const Vector2& InVectorPos, const LinearColor& InColor)
{
}

void OpenGLRSI::DrawPoint(const ScreenPoint& InScreenPos, const LinearColor& InColor)
{
}

void OpenGLRSI::DrawLine(const Vector2& InStartPos, const Vector2& InEndPos, const LinearColor& InColor)
{
}

void OpenGLRSI::DrawLine(const Vector4& InStartPos, const Vector4& InEndPos, const LinearColor& InColor)
{
}

float OpenGLRSI::GetDepthBufferValue(const ScreenPoint& InPos) const
{
	return 0.0f;
}

void OpenGLRSI::SetDepthBufferValue(const ScreenPoint& InPos, float InDepthValue)
{
}

void OpenGLRSI::DrawFullVerticalLine(int InX, const LinearColor& InColor)
{
}

void OpenGLRSI::DrawFullHorizontalLine(int InY, const LinearColor& InColor)
{
}

void OpenGLRSI::PushStatisticText(std::string&& InText)
{
	_StaticTexts.emplace_back(InText);

}

void OpenGLRSI::PushStatisticTexts(std::vector<std::string>&& InTexts)
{
	std::move(InTexts.begin(), InTexts.end(), std::back_inserter(_StaticTexts));
}

void OpenGLRSI::PushLogText(std::string&& InText)
{
	_PermanentLogs.emplace_back(InText);
}

void OpenGLRSI::PushLogTexts(std::vector<std::string>&& InTexts)
{
	std::move(InTexts.begin(), InTexts.end(), std::back_inserter(_PermanentLogs));
}

void OpenGLRSI::PushLogText(std::size_t& Hash, std::string&& InText)
{
	if (Hash == Math::InvalidHash)
	{
		_PermanentLogs.emplace_back(InText);
		return;
	}
	_TempLogs.emplace_back(std::make_pair(Hash, InText));
}

void OpenGLRSI::PushLogTexts(std::vector<std::pair<std::size_t, std::string>>& NewLogs)
{
	for (const auto& NewLog : NewLogs)
	{
		if (NewLog.first == Math::InvalidHash)
		{
			_PermanentLogs.emplace_back(NewLog.second);
			continue;
		}
		_TempLogs.emplace_back(std::make_pair(NewLog.first, NewLog.second));
	}
}

void OpenGLRSI::DeleteLogText(std::size_t& HashToDelete)
{
	if (HashToDelete == Math::InvalidHash)
	{
		return;
	}
	for (auto LogIter = _TempLogs.begin(); LogIter != _TempLogs.end(); ++LogIter)
	{
		if (LogIter->first == HashToDelete)
		{
			_TempLogs.erase(LogIter);
			return;
		}
	}
}

void OpenGLRSI::DeleteLogTexts(std::vector<std::size_t>& HashesToDelete)
{
	for (auto& HashToDelete : HashesToDelete)
	{
		DeleteLogText(HashToDelete);
	}
}

void OpenGLRSI::DrawOverlayTexts()
{
	if (_StaticTexts.empty() && _PermanentLogs.empty() && _TempLogs.empty())
	{
		return;
	}

	float w = (float)_ScreenSize.X;
	float h = (float)_ScreenSize.Y;

	Matrix4x4 ortho(
		Vector4(2.f / w, 0.f, 0.f, 0.f),
		Vector4(0.f, -2.f / h, 0.f, 0.f),
		Vector4(0.f, 0.f, 1.f, 0.f),
		Vector4(-1.f, 1.f, 0.f, 1.f)
	);
	
	static std::vector<unsigned char> vertexBuffer(_MaxOverlayQuads * 4 * 16);
	UINT32 totalQuads = 0;
	unsigned char statColor[4] = { 255, 255, 255, 255 };
	float y = 30.f;

	for (const std::string& line : _StaticTexts)
	{
		int quads = stb_easy_font_print(w - 270.f, y, const_cast<char*>(line.c_str()), statColor,
			vertexBuffer.data() + (size_t)totalQuads * 4 * 16, (int)(vertexBuffer.size() - (size_t)totalQuads * 4 * 16));
		totalQuads += quads;
		y += 20.f;
	}
	unsigned char logColor[4] = { 255, 255, 0, 255 };
	y = h - 20.f;
	for (const auto& log : _TempLogs)
	{
		int quads = stb_easy_font_print(10.f, y, const_cast<char*>(log.second.c_str()), logColor,
			vertexBuffer.data() + (size_t)totalQuads * 4 * 16, (int)(vertexBuffer.size() - (size_t)totalQuads * 4 * 16));
		totalQuads += quads;
		y -= 16.f;
	}
	for (const std::string& log : _PermanentLogs)
	{
		int quads = stb_easy_font_print(10.f, y, const_cast<char*>(log.c_str()), logColor,
			vertexBuffer.data() + (size_t)totalQuads * 4 * 16, (int)(vertexBuffer.size() - (size_t)totalQuads * 4 * 16));
		totalQuads += quads;
		y -= 16.f;
	}

	_Device.UpdateVertexBuffer(_OverlayMesh.VBO, vertexBuffer.data(), (size_t)totalQuads * 4 * 16);
	_Device.SetDepthTest(false);
	_Device.UseShader(_OverlayShader);
	_Device.SetUniformMat4(_OverlayShader, "uOrtho", ortho);
	_Device.BindMesh(_OverlayMesh);
	_Device.DrawIndexed(totalQuads * 6);
	_Device.SetDepthTest(true);

	_StaticTexts.clear();
}
