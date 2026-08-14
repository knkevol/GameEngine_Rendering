#version 330 core
#define MAX_POINT_LIGHTS 4

in vec4 vColor;
in vec2 vUV;
in vec3 vWorldPos;
in vec3 vWorldNormal;
in vec3 vTangent;
in vec4 vLightSpacePos;

uniform sampler2D uTexture;
uniform bool uUseTexture;
uniform vec4 uColor;

uniform vec4 uMaterialDiffuse;
uniform vec4 uMaterialSpecular;
uniform float uMaterialShininess;
uniform sampler2D uNormalMap;
uniform bool uUseNormalMap;
uniform sampler2D uMRAMap;
uniform bool uUseMRAMap;
uniform samplerCube uSkybox;
uniform bool uUseEnvReflection; // 반사효과 토글
uniform sampler2D uShadowMap;

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

vec3 CalcBlinnPhong(vec3 InLightDir, vec3 InLightColor, float InIntensity, vec3 InNormal, vec3 InViewDir, vec3 InDiffuseColor, vec3 InSpecularColor, float InShininess)
{
    float diff = max(dot(InNormal, InLightDir), 0.0);

    vec3 halfwayDir = normalize(InLightDir + InViewDir);
    float spec = pow(max(dot(InNormal, halfwayDir), 0.0), InShininess);

    vec3 diffuse = diff * InDiffuseColor * InLightColor * InIntensity;
    vec3 specular = spec * InSpecularColor * InLightColor * InIntensity;
    return diffuse + specular;
}

float CalcShadow(vec4 InLightSpacePos)
{
    // 직교 투영 
    vec3 projCoords = InLightSpacePos.xyz / InLightSpacePos.w;
    projCoords = projCoords * 0.5 + 0.5;

    if(projCoords.z > 1.0)
    {
        return 0.0;
    }

    float currentDepth = projCoords.z;
    float bias = 0.005; // shadow acne 방지

    vec2 texelSize = 1.0 / textureSize(uShadowMap, 0);

    float shadow = 0.0;
    for(int x = -1; x <= 1; ++x)
    {
        for(int y = -1; y <= 1; ++y)
        {
            float neighborDepth = texture(uShadowMap, projCoords.xy + vec2(x, y) * texelSize).r;
            shadow += currentDepth - bias > neighborDepth ? 1.0 : 0.0;
        }
    }

    shadow /= 9.0;

    return shadow;
}

void main()
{
    vec4 baseColor = uUseTexture ? texture(uTexture, vec2(vUV.x, 1.0 - vUV.y)) * vColor : vColor;
    baseColor *= uColor;

    vec3 diffuseColor = baseColor.rgb * uMaterialDiffuse.rgb;
    vec3 specularColor = uMaterialSpecular.rgb;
    float shininess = uMaterialShininess;

    vec3 normal = normalize(vWorldNormal);

    if(uUseNormalMap)
    {
        vec3 N = normal;
        vec3 T = normalize(vTangent - dot(vTangent, N) * N); // 재직교화
        vec3 B = cross(N, T);
        mat3 TBN = mat3(T, B, N);

        vec3 tangentNormal = texture(uNormalMap, vec2(vUV.x, 1.0 - vUV.y)).rgb * 2.0 - 1.0;
        normal = normalize(TBN * tangentNormal);
    }

    if(!gl_FrontFacing)
    {
        normal = -normal;
    }

    float ao = 1.0;
    float metallic = 0.0;
    if(uUseMRAMap)
    {
        vec3 mra = texture(uMRAMap, vec2(vUV.x, 1.0 - vUV.y)).rgb;
        metallic = mra.r;
        float roughness = mra.g;
        ao = mra.b;

        specularColor = mix(vec3(0.04), diffuseColor, metallic);
        shininess = mix(128.0, 4.0, roughness);
    }

    vec3 viewDir = normalize(uViewPosition.xyz - vWorldPos);
    vec3 result = 0.1 * diffuseColor * ao;

    // Directional Light
    {
        float shadow = CalcShadow(vLightSpacePos);
        vec3 lightDir = normalize(-uDirLightDirection.xyz);
        result += (1.0 - shadow) * CalcBlinnPhong(lightDir, uDirLightColor.rgb, uDirLightColor.a, normal, viewDir, diffuseColor, specularColor, shininess);
    }

    // Point Lights
    for (int i = 0; i < uPointLightCount; ++i)
    {
        vec3 toLight = uPointLights[i].Position.xyz - vWorldPos;
        float dist = length(toLight);
        vec3 lightDir = toLight / max(dist, 0.0001);

        float attenuation = 1.0 / (uPointLights[i].Attenuation.x + uPointLights[i].Attenuation.y * dist + uPointLights[i].Attenuation.z * dist * dist);

        result += CalcBlinnPhong(lightDir, uPointLights[i].Color.rgb, uPointLights[i].Color.a, normal, viewDir, diffuseColor, specularColor, shininess) * attenuation;
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

        result += CalcBlinnPhong(lightDir, uSpotColor.rgb, uSpotColor.a, normal, viewDir, diffuseColor, specularColor, shininess) * attenuation * spotIntensity;
    }

    // 환경맵 반사
    vec3 incident = -viewDir;
    vec3 reflectDir = reflect(incident, normal);
    vec3 envColor = texture(uSkybox, reflectDir).rgb;

    float envMix = uUseEnvReflection ? metallic : 0.0;
    result = mix(result, envColor, envMix);

    //FragColor = vec4(normal * 0.5 + 0.5, 1.0); // 디버그용 : 노멀맵
    //FragColor = vec4(envColor, 1.0); // 디버그용 : 반사색
    FragColor = vec4(result, baseColor.a);
}