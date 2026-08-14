#version 330 core
#define MAX_BONES 100

layout(location = 0) in vec4 aPosition;
layout(location = 3) in ivec4 aBoneIndices;
layout(location = 4) in vec4 aBoneWeights;

uniform mat4 uModel;
uniform mat4 uLightSpaceMatrix;
uniform mat4 uBoneMatrices[MAX_BONES];

void main()
{
	mat4 skinMatrix = aBoneWeights.x * uBoneMatrices[aBoneIndices.x]
					+ aBoneWeights.y * uBoneMatrices[aBoneIndices.y]
					+ aBoneWeights.z * uBoneMatrices[aBoneIndices.z]
					+ aBoneWeights.w * uBoneMatrices[aBoneIndices.w];
	gl_Position = uLightSpaceMatrix * uModel * skinMatrix * aPosition;
}