#version 330 core

layout(location = 0) in vec4 aPosition;
layout(location = 1) in vec4 aColor;
layout(location = 2) in vec2 aUV;

uniform mat4 uMVP;

out vec4 vColor;
out vec2 vUV;

void main()
{
      gl_Position = uMVP * aPosition;   // CPU의 "InMatrix * v.Position"과 동일한 연산
      vColor = aColor;
      vUV = aUV;
}