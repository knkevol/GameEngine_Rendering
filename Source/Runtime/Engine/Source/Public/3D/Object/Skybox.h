#pragma once

namespace GER
{
	class Skybox
	{
	public:
		Skybox() = default;
		~Skybox() {}

	public:
		void LoadFromFolder(const std::string& InFolderPath);

		bool IsInitialized() const { return _Width > 0 && _Height > 0; }
		UINT32 GetWidth() const { return _Width; }
		UINT32 GetHeight() const { return _Height; }

		void UploadToGPU(OpenGLDevice& InDevice);
		bool IsUploadToGPU() const { return _IsUploadedToGPU; }
		TextureHandle GetGPUHandle() const { return _GPUHandle; }

	private:
		void LoadFace(const std::string& InFilePath, std::vector<LinearColor>& OutFaceColors);

	private:
		std::vector<std::vector<LinearColor>> _FaceColors = std::vector<std::vector<LinearColor>>(6);

		UINT32 _Width;
		UINT32 _Height;

		TextureHandle _GPUHandle = 0;
		bool _IsUploadedToGPU = false;
	};

}