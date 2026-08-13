#pragma once

namespace GER
{

class Texture
{
public:
	Texture() = default;
	~Texture() { }

public:
	void Release();
	void LoadFromPath(const std::string& InFilePath);
	void LoadFromFile(FILE* InFilePtr);
	void LoadNormalFromFile(FILE* InFilePtr);
	void LoadMRAFromFile(FILE* InFilePtr);

	bool IsInitialized() const { return (_BaseColor.size() > 0); }
	UINT32 GetWidth() const { return _Width; }
	UINT32 GetHeight() const { return _Height; }
	UINT32 GetSize() const { return _Width * _Height; }
	LinearColor GetSample(Vector2 InUV) const;
	TextureFilterMode GetMagFilterMode() const { return _MagFilter; }
	TextureFilterMode GetMinFilterMode() const { return _MinFilter; }
	TextureAddressMode GetAddressMode() const { return _AddressMode; }
	bool IsAnisotropyEnabled() const { return _AnisotropyEnable; }
	float GetMaxAnisotropy() const { return _MaxAnisotropy; }

	std::vector<LinearColor>& GetBaseColor() { return _BaseColor; }
	std::vector<LinearColor>& GetNormal() { return _Normal; }
	std::vector<float>& GetSpecular() { return _Specular; }
	std::vector<LinearColor>& GetMRA() { return _MRA; }

	// 셰이더에 노멀맵을 바인딩할지 판단
	bool HasNormalMap() const { return _Normal.size() > 0; }
	TextureHandle GetNormalGPUHandle() const { return _NormalGPUHandle; }
	bool HasMRAMap() const { return _MRA.size() > 0; }
	TextureHandle GetMRAGPUHandle() const { return _MRAGPUHandle; }

	void UploadToGPU(OpenGLDevice& InDevice);
	bool IsUploadedToGPU() const { return _IsUploadedToGPU; }
	TextureHandle GetGPUHandle() const { return _GPUHandle; }

private:
	static constexpr BYTE _Channel = 4;
	std::vector<LinearColor> _BaseColor;
	std::vector<LinearColor> _Normal;
	TextureHandle _NormalGPUHandle = 0;
	std::vector<LinearColor> _MRA;
	TextureHandle _MRAGPUHandle = 0;
	std::vector<float> _Specular;

	UINT32 _Width = 0;
	UINT32 _Height = 0;

	TextureFilterMode _MagFilter = TextureFilterMode::Nearest;
	TextureFilterMode _MinFilter = TextureFilterMode::Nearest;
	TextureAddressMode _AddressMode = TextureAddressMode::Repeat;
	bool _AnisotropyEnable = false;
	float _MaxAnisotropy = 16.0f;

	TextureHandle _GPUHandle = 0;
	bool _IsUploadedToGPU = false;
};

}