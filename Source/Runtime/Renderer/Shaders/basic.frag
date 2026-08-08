#version 330 core
#define MAX_POINT_LIGHTS 4

in vec4 vColor;
in vec2 vUV;
in vec3 vWorldPos;
in vec3 vWorldNormal;

uniform sampler2D uTexture;
uniform bool uUseTexture;
uniform vec4 uColor;

uniform vec4 uMaterialDiffuse;
uniform vec4 uMaterialSpecular;
uniform float uMaterialShininess;

struct PointLight
{
    vec4 Position;
    vec4 Color;
    vec4 Attenuation;
};

layout(std140) uniform CameraBlock
{
    mat4 uView;
    mat4 uProjection;
    vec4 uViewPosition;
};

layout(std140) uniform LightBlock
{
    vec4 uDirLightDirection;
    vec4 uDirLightColor;
    PointLight uPointLights[MAX_POINT_LIGHTS];
    vec4 uSpotPosition;
    vec4 uSpotDirection;
    vec4 uSpotColor;
    vec4 uSpotAttenuation;
    vec4 uSpotCutoffAngles; // x = cos(내부각), y = cos(외부각)
    int uPointLightCount;
};


out vec4 FragColor;

vec3 CalcBlinnPhong(vec3 InLightDir, vec3 InLightColor, float InIntensity, vec3 InNormal, vec3 InViewDir, vec3 InDiffuseColor, vec3 InSpecularColor)
{
    float diff = max(dot(InNormal, InLightDir), 0.0);

    vec3 halfwayDir = normalize(InLightDir + InViewDir);
    float spec = pow(max(dot(InNormal, halfwayDir), 0.0), uMaterialShininess);

    vec3 diffuse = diff * InDiffuseColor * InLightColor * InIntensity;
    vec3 specular = spec * InSpecularColor * InLightColor * InIntensity;
    return diffuse + specular;
}

void main()
{
    vec4 baseColor = uUseTexture ? texture(uTexture, vec2(vUV.x, 1.0 - vUV.y)) * vColor : vColor;
    baseColor *= uColor;

    vec3 diffuseColor = baseColor.rgb * uMaterialDiffuse.rgb;
    vec3 specularColor = uMaterialSpecular.rgb;

    vec3 normal = normalize(vWorldNormal);
    vec3 viewDir = normalize(uViewPosition.xyz - vWorldPos);

    vec3 result = 0.1 * diffuseColor;

    // Directional Light
    {
        vec3 lightDir = normalize(-uDirLightDirection.xyz);
        result += CalcBlinnPhong(lightDir, uDirLightColor.rgb, uDirLightColor.a, normal, viewDir, diffuseColor, specularColor);
    }

    // Point Lights
    for (int i = 0; i < uPointLightCount; ++i)
    {
        vec3 toLight = uPointLights[i].Position.xyz - vWorldPos;
        float dist = length(toLight);
        vec3 lightDir = toLight / max(dist, 0.0001);

        float attenuation = 1.0 / (uPointLights[i].Attenuation.x + uPointLights[i].Attenuation.y * dist + uPointLights[i].Attenuation.z * dist * dist);

        result += CalcBlinnPhong(lightDir, uPointLights[i].Color.rgb, uPointLights[i].Color.a, normal, viewDir, diffuseColor, specularColor) * attenuation;
    }

    // Spot Light
    {
        vec3 toLight = uSpotPosition.xyz - vWorldPos;
        float dist = length(toLight);
        vec3 lightDir = toLight / max(dist, 0.0001);

        float attenuation = 1.0 / (uSpotAttenuation.x + uSpotAttenuation.y * dist + uSpotAttenuation.z * dist * dist);

        float theta = dot(lightDir, normalize(-uSpotDirection.xyz));
        float epsilon = uSpotCutoffAngles.x - uSpotCutoffAngles.y;
        float spotIntensity = clamp((theta - uSpotCutoffAngles.y) / max(epsilon, 0.0001), 0.0, 1.0);

        result += CalcBlinnPhong(lightDir, uSpotColor.rgb, uSpotColor.a, normal, viewDir, diffuseColor, specularColor) * attenuation * spotIntensity;
    }

     FragColor = vec4(result, baseColor.a);
}