#include "Precompiled.h"

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

GPUMeshHandle GER::OpenGLDevice::CreateMesh(const void* InVertexData, size_t InVertexBytes, const UINT32* InIndices, UINT32 InIndexCount)
{
    GPUMeshHandle mesh;

    glGenVertexArrays(1, &mesh.VAO);
    glBindVertexArray(mesh.VAO);

    mesh.VBO = CreateVertexBuffer(InVertexData, InVertexBytes);
    mesh.EBO = CreateIndexBuffer(InIndices, InIndexCount);
    mesh.IndexCount = InIndexCount;

    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(DDD::Vertex3D), (void*)offsetof(DDD::Vertex3D, Position));
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(DDD::Vertex3D), (void*)offsetof(DDD::Vertex3D, Color));
    glEnableVertexAttribArray(1);

    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(DDD::Vertex3D), (void*)offsetof(DDD::Vertex3D, UV));
    glEnableVertexAttribArray(2);

    glBindVertexArray(0); // VAO 편집모드 종료

    return mesh;
}

void GER::OpenGLDevice::UseShader(ShaderHandle InShader)
{
    glUseProgram(InShader);
}

void GER::OpenGLDevice::SetUniformMat4(ShaderHandle InShader, const char* InName, const Matrix4x4& InMatrix)
{
    glUseProgram(InShader);
    int location = glGetUniformLocation(InShader, InName); // 변수 이름을 GPU 내부 슬롯 번호로 변환
    if (location >= 0)
    {
        glUniformMatrix4fv(location, 1, GL_FALSE, &InMatrix.Cols[0].X);
    }
}

void GER::OpenGLDevice::SetUniformMat4Array(ShaderHandle InShader, const char* InName, const std::vector<Matrix4x4>& InMatrices)
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

void GER::OpenGLDevice::BindMesh(const GPUMeshHandle& InMesh)
{
    glBindVertexArray(InMesh.VAO);
}

void GER::OpenGLDevice::DrawIndexed(UINT32 InIndexCount)
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

bool GER::OpenGLDevice::CheckProgramLink(UINT32 InProgram)
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
