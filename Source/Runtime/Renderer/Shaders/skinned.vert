#version 330 core
#define MAX_BONES 100

layout(location = 0) in vec4 aPosition;
layout(location = 1) in vec4 aColor;
layout(location = 2) in vec2 aUV;
layout(location = 3) in ivec4 aBoneIndices;
layout(location = 4) in vec4 aBoneWeights;

uniform mat4 uMVP;
uniform mat4 uBoneMatrices[MAX_BONES];

out vec4 vColor;
out vec2 vUV;

void main()
{
    mat4 skinMatrix = aBoneWeights.x * uBoneMatrices[aBoneIndices.x]
                     + aBoneWeights.y * uBoneMatrices[aBoneIndices.y]
                     + aBoneWeights.z * uBoneMatrices[aBoneIndices.z]
                     + aBoneWeights.w * uBoneMatrices[aBoneIndices.w];

    gl_Position = uMVP * skinMatrix * aPosition;
    vColor = aColor;
    vUV = aUV;
}