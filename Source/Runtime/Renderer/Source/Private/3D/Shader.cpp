#include "Precompiled.h"
#include <fstream>
#include <sstream>
using namespace GER::DDD;

std::string GER::DDD::LoadShaderSource(const std::string& InPath)
{
    std::ifstream file(InPath);
    if (!file.is_open())
    {
        OutputDebugStringA("Shader file open failed: ");
        OutputDebugStringA(InPath.c_str());
        OutputDebugStringA("\n");
        return std::string();
    }

    std::stringstream buffer;
    buffer << file.rdbuf();   // 파일 전체 내용을 문자열 버퍼로 통째로 읽음
    return buffer.str();
}