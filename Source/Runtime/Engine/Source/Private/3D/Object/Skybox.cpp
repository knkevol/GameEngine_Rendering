#include "Precompiled.h"

#pragma warning( push )
#pragma warning( disable : 26541 )
#include "Stb/stb_image.h"
#pragma warning ( pop )

namespace
{
	const char* FaceFileNames[6] = { "right", "left", "top", "bottom", "front", "back" };
}

void Skybox::LoadFromFolder(const std::string& InFolderPath)
{
	for (int face = 0; face < 6; ++face)
	{
		std::string filePath = InFolderPath + "/" + FaceFileNames[face] + ".jpg";
		LoadFace(filePath, _FaceColors[face]);
	}
}

void Skybox::UploadToGPU(OpenGLDevice& InDevice)
{
	if (_IsUploadedToGPU || !IsInitialized())
	{
		return;
	}

	std::vector<const void*> facePixelData(6);
	for (int face = 0; face < 6; ++face)
	{
		facePixelData[face] = _FaceColors[face].data();
	}

	_GPUHandle = InDevice.CreateCubemapTexture(facePixelData, _Width, _Height);
	_IsUploadedToGPU = true;
}

void Skybox::LoadFace(const std::string& InFilePath, std::vector<LinearColor>& OutFaceColors)
{
	FILE* f = nullptr;
	if (fopen_s(&f, InFilePath.c_str(), "rb") != 0 || f == nullptr)
	{
		return;
	}

	int width = 0, height = 0, channel = 0;
	stbi_uc* pixelPtr = stbi_load_from_file(f, &width, &height, &channel, STBI_rgb_alpha);
	fclose(f);

	if (pixelPtr == nullptr)
	{
		return;
	}

	_Width = static_cast<UINT32>(width);
	_Height = static_cast<UINT32>(height);

	size_t pixelNumbers = static_cast<size_t>(width) * static_cast<size_t>(height);
	OutFaceColors.reserve(pixelNumbers);
	for (int j = 0; j < height; j++)
	{
		for (int i = 0; i < width; i++)
		{
			size_t ix = (static_cast<size_t>(j) * width + i) * 4;
			Color32 c(pixelPtr[ix], pixelPtr[ix + 1], pixelPtr[ix + 2], pixelPtr[ix + 3]);
			OutFaceColors.push_back(LinearColor(c));
		}
	}

	stbi_image_free(pixelPtr);
}
