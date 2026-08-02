#pragma once

namespace GER
{
	using GPUBufferHandle = UINT32;
	using ShaderHandle = UINT32;

	struct GPUMeshHandle
	{
		UINT32 VAO = 0;
		UINT32 VBO = 0;
		UINT32 EBO = 0;
		UINT32 IndexCount = 0;
	};

	class OpenGLDevice
	{
	public:
		// cpu 정점데이터를 gpu에 복사 후 저장 공간을 가리키는 ID(vbo) 리턴
		GPUBufferHandle CreateVertexBuffer(const void* InData, size_t InBytes);
		// 정점 중복 저장 방지 참조 리스트
		GPUBufferHandle CreateIndexBuffer(const UINT32* InIndices, size_t InCount);
		// GLSL를 gpu가 실행가능한 형태로 컴파일 및 링크하여 결과 프로그램 ID를 리턴
		ShaderHandle CreateShaderProgram(const char* InVsSrc, const char* InFsSrc);

		// VBO, EBO, VAO를 한번에 처리하는 함수
		GPUMeshHandle CreateMesh(const void* InVertexData, size_t InVertexBytes, const UINT32* InIndices, UINT32 InIndexCount);

		// 셰이더 지정 (한번에 한 셰이더만 활성화 가능)
		void UseShader(ShaderHandle InShader);
		// 셰이더 안 uniform 변수에 cpu쪽 marix값을 채워 넣음.
		void SetUniformMat4(ShaderHandle InShader, const char* InName, const Matrix4x4& InMatrix);
		void SetUniformMat4Array(ShaderHandle InShader, const char* InName, const std::vector<Matrix4x4>& InMatrices);

		// 메시(VAO)를 그릴 준비
		void BindMesh(const GPUMeshHandle& InMesh);
		// 바인딩 된 메시를 활성화된 셰이더로 그리도록 gpu에 지시하는 드로우콜
		void DrawIndexed(UINT32 InIndexCount);

	private:
		bool CheckShaderCompile(UINT32 InShader, const char* InStageName);
		bool CheckProgramLink(UINT32 InProgram);
	};
}