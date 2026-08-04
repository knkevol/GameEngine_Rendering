#include "Precompiled.h"
using namespace GER::DDD;

GPUBufferHandle OpenGLDevice::CreateVertexBuffer(const void* InData, size_t InBytes)
{
    UINT32 vbo = 0;
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, InBytes, InData, GL_STATIC_DRAW);
    return vbo;
}

GPUBufferHandle OpenGLDevice::CreateIndexBuffer(const UINT32* InIndices, size_t InCount)
{
    UINT32 ebo = 0;
    glGenBuffers(1, &ebo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, InCount * sizeof(UINT32), InIndices, GL_STATIC_DRAW);
    return ebo;
}

ShaderHandle OpenGLDevice::CreateShaderProgram(const char* InVsSrc, const char* InFsSrc)
{
    UINT32 vs = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vs, 1, &InVsSrc, nullptr);
    glCompileShader(vs);
    CheckShaderCompile(vs, "Vertex");

    UINT32 fs = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fs, 1, &InFsSrc, nullptr);
    glCompileShader(fs);
    CheckShaderCompile(fs, "Fragment");

    UINT32 program = glCreateProgram();
    glAttachShader(program, vs);
    glAttachShader(program, fs);
    glLinkProgram(program);
    CheckProgramLink(program);

    glDeleteShader(vs);
    glDeleteShader(fs);

    return program;
}

GPUMeshHandle OpenGLDevice::CreateMesh(const void* InVertexData, size_t InVertexBytes, const UINT32* InIndices, UINT32 InIndexCount)
{
    GPUMeshHandle mesh;

    glGenVertexArrays(1, &mesh.VAO);
    glBindVertexArray(mesh.VAO);

    mesh.VBO = CreateVertexBuffer(InVertexData, InVertexBytes);
    mesh.EBO = CreateIndexBuffer(InIndices, InIndexCount);
    mesh.IndexCount = InIndexCount;

    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex3D), (void*)offsetof(Vertex3D, Position));
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex3D), (void*)offsetof(Vertex3D, Color));
    glEnableVertexAttribArray(1);

    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex3D), (void*)offsetof(Vertex3D, UV));
    glEnableVertexAttribArray(2);

    glBindVertexArray(0); // VAO 편집모드 종료

    return mesh;
}

TextureHandle OpenGLDevice::CreateTexture(const void* InPixelData, UINT32 InWidth, UINT32 InHeight)
{
    UINT32 texture = 0;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA32F, InWidth, InHeight, 0, GL_RGBA, GL_FLOAT, InPixelData);
    glGenerateMipmap(GL_TEXTURE_2D);
    
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glBindTexture(GL_TEXTURE_2D, 0);

    return texture;
}

GPUMeshHandle OpenGLDevice::CreateSkinnedMesh(const void* InVertexData, size_t InVertexBytes, const UINT32* InIndices, UINT32 InIndexCount)
{
    GPUMeshHandle mesh;

    //VAO 생성 및 바인딩
    glGenVertexArrays(1, &mesh.VAO);
    glBindVertexArray(mesh.VAO);

    // VBO(정점버퍼), EBO(인덱스버퍼) Upload to GPU
    mesh.VBO = CreateVertexBuffer(InVertexData, InVertexBytes);
    mesh.EBO = CreateIndexBuffer(InIndices, InIndexCount);
    mesh.IndexCount = InIndexCount;

    // 3) attribute 0~2: 위치/색/UV
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(SkinnedVertex3D), (void*)offsetof(SkinnedVertex3D, Position));
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(SkinnedVertex3D), (void*)offsetof(SkinnedVertex3D, Color));
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(SkinnedVertex3D), (void*)offsetof(SkinnedVertex3D, UV));
    glEnableVertexAttribArray(2);
    // 4) attribute 3: 본 인덱스 — 정수는 반드시 'I' 버전(glVertexAttribIPointer)을 써야 0~1로 정규화되지 않음
    glVertexAttribIPointer(3, 4, GL_INT, sizeof(SkinnedVertex3D), (void*)offsetof(SkinnedVertex3D, BoneIndices));
    glEnableVertexAttribArray(3);
    // 5) attribute 4: 본 가중치
    glVertexAttribPointer(4, 4, GL_FLOAT, GL_FALSE, sizeof(SkinnedVertex3D), (void*)offsetof(SkinnedVertex3D, BoneWeights));
    glEnableVertexAttribArray(4);
    

    glBindVertexArray(0);

    return mesh;
}

void OpenGLDevice::BindTexture(TextureHandle InTexture, UINT32 InSlot)
{
    glActiveTexture(GL_TEXTURE0 + InSlot);
    glBindTexture(GL_TEXTURE_2D, InTexture);
}

void OpenGLDevice::UseShader(ShaderHandle InShader)
{
    glUseProgram(InShader);
}

void OpenGLDevice::SetUniformMat4(ShaderHandle InShader, const char* InName, const Matrix4x4& InMatrix)
{
    glUseProgram(InShader);
    int location = glGetUniformLocation(InShader, InName); // 변수 이름을 GPU 내부 슬롯 번호로 변환
    if (location >= 0)
    {
        glUniformMatrix4fv(location, 1, GL_FALSE, &InMatrix.Cols[0].X);
    }
}

void OpenGLDevice::SetUniformMat4Array(ShaderHandle InShader, const char* InName, const std::vector<Matrix4x4>& InMatrices)
{
    if (InMatrices.empty())
    {
        return;
    }

    glUseProgram(InShader);
    int location = glGetUniformLocation(InShader, InName);
    if (location >= 0)
    {
        glUniformMatrix4fv(location, (GLsizei)InMatrices.size(), GL_FALSE, &InMatrices[0].Cols[0].X);
    }
}

void OpenGLDevice::SetUniformInt(ShaderHandle InShader, const char* InName, int InValue)
{
    glUseProgram(InShader);
    int location = glGetUniformLocation(InShader, InName);
    if (location >= 0)
    {
        glUniform1i(location, InValue);
    }
}

void OpenGLDevice::SetUniformFloat(ShaderHandle InShader, const char* InName, float InValue)
{
    // DepthBuffer 셰이더의 near/far 값 전달용
    glUseProgram(InShader);
    int location = glGetUniformLocation(InShader, InName);
    if (location >= 0)
    {
        glUniform1f(location, InValue);
    }
}

void OpenGLDevice::SetUniformColor(ShaderHandle InShader, const char* InName, const LinearColor& InColor)
{
    glUseProgram(InShader);
    int location = glGetUniformLocation(InShader, InName);
    if (location >= 0)
    {
        glUniform4f(location, InColor.R, InColor.G, InColor.B, InColor.A);
    }
}

void OpenGLDevice::SetPolygonMode(bool InWireframe)
{
    glPolygonMode(GL_FRONT_AND_BACK, InWireframe ? GL_LINE : GL_FILL);
}

void OpenGLDevice::BindMesh(const GPUMeshHandle& InMesh)
{
    glBindVertexArray(InMesh.VAO);
}

void OpenGLDevice::DrawIndexed(UINT32 InIndexCount)
{
    glDrawElements(GL_TRIANGLES, InIndexCount, GL_UNSIGNED_INT, nullptr);
}

bool OpenGLDevice::CheckShaderCompile(UINT32 InShader, const char* InStageName)
{
    int success = 0;
    glGetShaderiv(InShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        char log[512];
        glGetShaderInfoLog(InShader, sizeof(log), nullptr, log);
        OutputDebugStringA(InStageName);
        OutputDebugStringA(" shader compile error: \n");
        OutputDebugStringA(log);
    }

    return success != 0;
}

bool OpenGLDevice::CheckProgramLink(UINT32 InProgram)
{
    int success = 0;
    glGetProgramiv(InProgram, GL_LINK_STATUS, &success);
    if (!success)
    {
        char log[512];
        glGetShaderInfoLog(InProgram, sizeof(log), nullptr, log);
        OutputDebugStringA(" shader program link error: \n");
        OutputDebugStringA(log);

    }
    return success != 0;
}
