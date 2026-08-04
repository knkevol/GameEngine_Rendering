#version 330 core

in vec4 vColor;
in vec2 vUV;

uniform sampler2D uTexture;
uniform bool uUseTexture;
uniform vec4 uColor;

out vec4 FragColor;

void main()
{
    vec4 baseColor = uUseTexture ? texture(uTexture, vec2(vUV.x, 1.0 - vUV.y)) * vColor : vColor;
    FragColor = baseColor * uColor;
}