#version 330 core

uniform float uNearZ;
uniform float uFarZ;

out vec4 FragColor;

void main()
{
    float ndcZ = gl_FragCoord.z * 2.0 - 1.0;
    float linearDepth = (2.0 * uNearZ * uFarZ) / (uFarZ + uNearZ - ndcZ * (uFarZ - uNearZ));
    float grayScale = (linearDepth - uNearZ) / (uFarZ - uNearZ);
    FragColor = vec4(vec3(grayScale), 1.0);
}