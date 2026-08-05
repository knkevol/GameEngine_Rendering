#pragma once

namespace GER
{
	class OpenGLRSI : public RendererInterface
	{
	public:
		OpenGLRSI() = default;
		~OpenGLRSI();

	public:
        // 활성화된 HWND를 얻어 GLContext 초기화
		virtual bool Init(const ScreenPoint& InScreenSize) override;
        virtual void Shutdown() override;
        virtual bool IsInitialized() const override { return _Initialized; }

        virtual void Clear(const LinearColor& InClearColor) override;
        virtual void BeginFrame() override;
        virtual void EndFrame() override;

        virtual void DrawPoint(const Vector2& InVectorPos, const LinearColor& InColor) override;
        virtual void DrawPoint(const ScreenPoint& InScreenPos, const LinearColor& InColor) override;
        virtual void DrawLine(const Vector2& InStartPos, const Vector2& InEndPos, const LinearColor& InColor) override;
        virtual void DrawLine(const Vector4& InStartPos, const Vector4& InEndPos, const LinearColor& InColor) override;

        virtual float GetDepthBufferValue(const ScreenPoint& InPos) const override;
        virtual void SetDepthBufferValue(const ScreenPoint& InPos, float InDepthValue) override;

        virtual void DrawFullVerticalLine(int InX, const LinearColor& InColor) override;
        virtual void DrawFullHorizontalLine(int InY, const LinearColor& InColor) override;

        virtual void PushStatisticText(std::string&& InText) override;
        virtual void PushStatisticTexts(std::vector<std::string>&& InTexts) override;

        virtual void PushLogText(std::string&& InText) override;
        virtual void PushLogTexts(std::vector<std::string>&& InTexts) override;

        virtual void PushLogText(std::size_t& Hash, std::string&& InText) override;
        virtual void PushLogTexts(std::vector<std::pair<std::size_t, std::string>>& NewLogs) override;

        virtual void DeleteLogText(std::size_t& HashToDelete) override;
        virtual void DeleteLogTexts(std::vector<std::size_t>& HashesToDelete) override;

        // SoftRenderer가 실제 메시를 그릴 때 OpenGLDevice로 접근할 수 있게 함.
        OpenGLDevice& GetDevice() { return _Device; }

    private:
        bool _Initialized = false;
        ScreenPoint _ScreenSize;
        WindowsGLContext _GLContext;
        OpenGLDevice _Device;

        std::vector<std::string> _StaticTexts;
        std::vector<std::string> _PermanentLogs;
        std::vector<std::pair<std::size_t, std::string>> _TempLogs;

        ShaderHandle _OverlayShader = 0;
        GPUMeshHandle _OverlayMesh;
        static constexpr UINT32 _MaxOverlayQuads = 4000;

    private:
        void DrawOverlayTexts();
        
	};
}