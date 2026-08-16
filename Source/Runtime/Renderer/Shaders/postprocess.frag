#version 330 core

in vec2 vUV;
out vec4 FragColor;

uniform sampler2D uSceneColor;
uniform float uExposure;
uniform float uGamma;

void main()
{
	vec3 hdrColor = texture(uSceneColor, vUV).rgb;
	vec3 exposed = hdrColor * uExposure;
	// Reinhard Tone Mapping
	vec3 mapped = exposed / (exposed + vec3(1.0));

	vec3 final = pow(mapped, vec3(1.0 / uGamma));

	FragColor = vec4(final, 1.0);
}