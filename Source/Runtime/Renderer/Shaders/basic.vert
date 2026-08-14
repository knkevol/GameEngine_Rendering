#version 330 core

layout(location = 0) in vec4 aPosition;
layout(location = 1) in vec4 aColor;
layout(location = 2) in vec2 aUV;
layout(location = 3) in vec3 aNormal;
layout(location = 4) in vec3 aTangent;

layout(std140) uniform CameraBlock
{
    mat4 uView;
    mat4 uProjection;
    vec4 uViewPosition;
};

uniform mat4 uModel;
uniform mat4 uLightSpaceMatrix;

out vec4 vColor;
out vec2 vUV;
out vec3 vWorldPos;
out vec3 vWorldNormal;
out vec3 vTangent;
out vec4 vLightSpacePos;

void main()
{
    vec4 worldPos = uModel * aPosition;
    gl_Position = uProjection * uView * worldPos; // = MVP

    vColor = aColor;
    vUV = aUV;
    vWorldPos = worldPos.xyz;

    // 이동 영향 X, 비균일 스케일은 그냥 곱할 시 왜곡되어 역전치 행렬로 변환
    vWorldNormal = normalize(mat3(transpose(inverse(uModel))) * aNormal);
    vTangent = normalize(mat3(uModel) * aTangent);

    vLightSpacePos = uLightSpaceMatrix * worldPos;
}