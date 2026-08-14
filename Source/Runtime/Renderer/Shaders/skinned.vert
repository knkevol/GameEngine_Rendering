#version 330 core
#define MAX_BONES 100

layout(location = 0) in vec4 aPosition;
layout(location = 1) in vec4 aColor;
layout(location = 2) in vec2 aUV;
layout(location = 3) in ivec4 aBoneIndices;
layout(location = 4) in vec4 aBoneWeights;
layout(location = 5) in vec3 aNormal;
layout(location = 6) in vec3 aTangent;

layout(std140) uniform CameraBlock
{
    mat4 uView;
    mat4 uProjection;
    vec4 uViewPosition;
};

uniform mat4 uModel;
uniform mat4 uBoneMatrices[MAX_BONES];
uniform mat4 uLightSpaceMatrix;

out vec4 vColor;
out vec2 vUV;
out vec3 vWorldPos;
out vec3 vWorldNormal;
out vec3 vTangent;
out vec4 vLightSpacePos;

void main()
{
    mat4 skinMatrix = aBoneWeights.x * uBoneMatrices[aBoneIndices.x]
                     + aBoneWeights.y * uBoneMatrices[aBoneIndices.y]
                     + aBoneWeights.z * uBoneMatrices[aBoneIndices.z]
                     + aBoneWeights.w * uBoneMatrices[aBoneIndices.w];

    vec4 worldPos = uModel * skinMatrix * aPosition;
    gl_Position = uProjection * uView * worldPos;
    vColor = aColor;
    vUV = aUV;
    vWorldPos = worldPos.xyz;

    mat3 skinNormalMatrix = mat3(transpose(inverse(uModel * skinMatrix)));
    vWorldNormal = normalize(skinNormalMatrix * aNormal);
    vTangent = normalize(mat3(uModel * skinMatrix) * aTangent);

    vLightSpacePos = uLightSpaceMatrix * worldPos;
}