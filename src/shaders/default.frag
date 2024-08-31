#version 330 core

out vec4 FragColor;

in vec3 WorldPos;
in vec2 TexCoord;
in vec3 Normal;


// material
uniform sampler2D albedoMap;
uniform sampler2D normalMap;
uniform sampler2D metallicMap;
uniform sampler2D roughnessMap;
uniform sampler2D aoMap;

// lights
uniform int lightNum;
uniform vec3 lightPositions[4];
uniform vec3 lightColors[4];

// camera
uniform vec3 cameraPosition;


#define PI 3.1415926


float DistributionGGX(vec3 N, vec3 H, float roughness)
{
    float alpha = pow(roughness, 2);
    float alpha2 = pow(alpha, 2);

    float NdotH = max(dot(N, H), 0.0);
    float NdotH2 = pow(NdotH, 2);

    float numerator = alpha2;
    float denominator = PI * pow(NdotH2 * (alpha2 - 1.0) + 1.0, 2.0);

    return numerator / denominator;
}

float GeometrySchlickGGX(float NdotVorL, float roughness)
{
    float k = pow(roughness + 1.0, 2.0) / 8.0;

    float numerator = NdotVorL;
    float denominator = NdotVorL * (1 - k) + k;

    return numerator / denominator;
}

float GeometrySmith(vec3 N, vec3 V, vec3 L, float roughness)
{
    float NdotV = max(dot(N, V), 0.0);
    float NdotL = max(dot(N, L), 0.0);

    float ggx2 = GeometrySchlickGGX(NdotV, roughness);
    float ggx1 = GeometrySchlickGGX(NdotL, roughness);

    return ggx1 * ggx2;
}

vec3 FresnelSchlick(float cosTheta, vec3 F0)
{
    return F0 + (1.0 - F0) * pow(clamp(1.0 - cosTheta, 0.0, 1.0), 5.0);
}

vec3 getNormalFromMap()
{
    vec3 tangentNormal = texture(normalMap, TexCoord).xyz * 2.0 - 1.0;

    vec3 Q1  = dFdx(WorldPos);
    vec3 Q2  = dFdy(WorldPos);
    vec2 st1 = dFdx(TexCoord);
    vec2 st2 = dFdy(TexCoord);

    vec3 N   = normalize(Normal);
    vec3 T  = normalize(Q1*st2.t - Q2*st1.t);
    vec3 B  = -normalize(cross(N, T));
    mat3 TBN = mat3(T, B, N);

    return normalize(TBN * tangentNormal);
}

void main()
{
    vec3 albedo = pow(texture(albedoMap, TexCoord).rgb, vec3(2.2));
    vec3 normal = getNormalFromMap();
    float metallic = texture(metallicMap, TexCoord).r;
    float roughness = texture(roughnessMap, TexCoord).r;
    float ao = texture(aoMap, TexCoord).r;


    // using normal map
    vec3 N = normalize(normal);
    vec3 V = normalize(cameraPosition - WorldPos);

    vec3 F0 = vec3(0.04);
    F0 = mix(F0, albedo, metallic);

    vec3 Lo = vec3(0.0);

    for(int i = 0; i < lightNum; ++i) {
        vec3 L = normalize(lightPositions[i] - WorldPos);
        vec3 H = normalize(V + L);
        float dist = length(lightPositions[i] - WorldPos);
        float attenuation = 1.0 / pow(dist, 2.0);
        vec3 radiance = lightColors[i] * attenuation;

        float NDF = DistributionGGX(N, H, roughness);
        float G = GeometrySmith(N, V, L, roughness);
        vec3 F = FresnelSchlick(clamp(dot(H, V), 0.0, 1.0), F0);

        vec3 numerator = NDF * G * F;
        float denominator = 4.0 * max(dot(N, V), 0.0) * max(dot(N, L), 0.0) + 0.0001;
        vec3 specular = numerator / denominator;

        vec3 Ks = F;
        vec3 Kd = vec3(1.0) - Ks;

        Kd *= 1.0 - metallic;

        float NdotL = max(dot(N, L), 0.0);

        Lo += (Kd * albedo / PI + specular) * radiance * NdotL;
    }

    vec3 ambient = vec3(0.03) * albedo * ao;
    vec3 color = ambient + Lo;

    // HDR tone mapping
    color = color / (color + vec3(1.0));

    color = pow(color, vec3(1.0 / 2.2));

    FragColor = vec4(color, 1.0);


}
