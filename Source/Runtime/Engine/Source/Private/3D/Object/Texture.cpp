#include "Precompiled.h"

#define STB_IMAGE_IMPLEMENTATION
#pragma warning( push )
#pragma warning( disable : 26541 )
#include "Stb/stb_image.h"
#pragma warning( pop )

void Texture::Release()
{
	_Width = 0;
	_Height = 0;
	_BaseColor.clear();
	_Normal.clear();
	_MRA.clear();
	_Specular.clear();
}

void Texture::LoadFromPath(const std::string& InFilePath)
{
	std::string TargetFilePath = InFilePath + "diffuse.png";

	FILE* f = NULL;
	if (0 == fopen_s(&f, TargetFilePath.c_str(), "rb"))
	{
		LoadFromFile(f);
	}

	std::string NormalPath = InFilePath + "normal.png";
	FILE* fn = NULL;
	if (0 == fopen_s(&fn, NormalPath.c_str(), "rb"))
	{
		LoadNormalFromFile(fn);
	}

	std::string MRAPath = InFilePath + "MRA.png";
	FILE* fm = NULL;
	if (0 == fopen_s(&fm, MRAPath.c_str(), "rb"))
	{
		LoadMRAFromFile(fm);
	}
	
}

void Texture::LoadFromFile(FILE* InFilePtr)
{
	if (InFilePtr == NULL)
	{
		return;
	}

	Release();

	int width = 0, height = 0, channel = 0;
	stbi_uc* pixelsPtr = stbi_load_from_file(InFilePtr, &width, &height, &channel, STBI_rgb_alpha);
	if (pixelsPtr == NULL)
	{
		return;
	}

	_Width = static_cast<UINT32>(width);
	_Height = static_cast<UINT32>(height);
	size_t pixelNumbers = static_cast<size_t>(_Width) * static_cast<size_t>(_Height);
	_BaseColor.reserve(pixelNumbers);
	for (size_t j = 0; j < _Height; j++)
	{
		for (size_t i = 0; i < _Width; i++)
		{
			size_t ix = (j * _Width + i) * 4;
			Color32 c(pixelsPtr[ix], pixelsPtr[ix + 1], pixelsPtr[ix + 2], pixelsPtr[ix + 3]);
			_BaseColor.push_back(LinearColor(c));
		}
	}

	OutputDebugString("Texture Load Completed \n");
	char buffer[50];
	sprintf(buffer, "Texture %d x %d \n", _Width, _Height);
	OutputDebugString(buffer);
	return;
}

void Texture::LoadNormalFromFile(FILE* InFilePtr)
{
	if (InFilePtr == NULL)
	{
		return;
	}

	int width = 0, height = 0, channel = 0;
	stbi_uc* pixelsPtr = stbi_load_from_file(InFilePtr, &width, &height, &channel, STBI_rgb_alpha);
	if (pixelsPtr == NULL)
	{
		return;
	}

	// 0~255 정수픽셀을 float로 변환하여 _Normal에 채움
	size_t pixelNumbers = static_cast<size_t>(width) * static_cast<size_t>(height);
	_Normal.reserve(pixelNumbers);
	for (int j = 0; j < height; j++)
	{
		for (int i = 0; i < width; i++)
		{
			size_t ix = (static_cast<size_t>(j) * width + i) * 4;
			Color32 c(pixelsPtr[ix], pixelsPtr[ix + 1], pixelsPtr[ix + 2], pixelsPtr[ix + 3]);
			_Normal.push_back(LinearColor(c));
		}
	}
}

void Texture::LoadMRAFromFile(FILE* InFilePtr)
{
	if (InFilePtr == NULL)
	{
		return;
	}

	int width = 0, height = 0, channel = 0;
	stbi_uc* pixelsPtr = stbi_load_from_file(InFilePtr, &width, &height, &channel, STBI_rgb_alpha);
	if (pixelsPtr == NULL)
	{
		return;
	}

	size_t pixelNumbers = static_cast<size_t>(width) * static_cast<size_t>(height);
	_MRA.reserve(pixelNumbers);
	for (int j = 0; j < height; j++)
	{
		for (int i = 0; i < width; i++)
		{
			size_t ix = (static_cast<size_t>(j) * width + i) * 4;
			Color32 c(pixelsPtr[ix], pixelsPtr[ix + 1], pixelsPtr[ix + 2], pixelsPtr[ix + 3]);
			_MRA.push_back(LinearColor(c));
		}
	}
}

LinearColor Texture::GetSample(Vector2 InUV) const
{
	if (!IsInitialized())
	{
		return LinearColor::Error;
	}

	int x = Math::FloorToInt(InUV.X * _Width) % _Width;
	int y = Math::FloorToInt(InUV.Y * _Height) % _Height;
	int index = _Width * (_Height - (1 + y)) + x;

	if (index >= _BaseColor.size())
	{
		return LinearColor::Error;
	}

	return _BaseColor[index];
}

void Texture::UploadToGPU(OpenGLDevice& InDevice)
{
	if (_IsUploadedToGPU || !IsInitialized())
	{
		return;
	}

	_GPUHandle = InDevice.CreateTexture(_BaseColor.data(), _Width, _Height);

	if (HasNormalMap())
	{
		_NormalGPUHandle = InDevice.CreateTexture(_Normal.data(), _Width, _Height);
	}

	if (HasMRAMap())
	{
		_MRAGPUHandle = InDevice.CreateTexture(_MRA.data(), _Width, _Height);
	}

	_IsUploadedToGPU = true;
}
