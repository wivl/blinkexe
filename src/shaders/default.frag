#version 330 core

out vec4 FragColor;

in vec4 position;
in vec2 texcoord;
in vec3 normal;


uniform sampler2D albedo;

uniform vec3 cameraPosition;
vec3 lightPosition = vec3(4, 5, 3);
vec3 lightColor = vec3(3.0, 3.0, 3.0);
vec3 emissivityMesh = vec3(0.0);
float roughness = 0.0;
float metallic = 0.0;
// uniform vec3 baseReflectance;

#define PI 3.1415926

// NDF(GGXTR)
// alpha: 表面粗糙度
// N: 表面法线
// H: half-way 向量
float D(float alpha, vec3 N, vec3 H) {
    // 分子
    float numberator = pow(alpha, 2.0);

    // 分母
    float NdotH = max(dot(N, H), 0.0);
    float denominator = PI * pow(pow(NdotH, 2.0) * (pow(alpha, 2.0) - 1.0) + 1.0, 2.0);
    denominator = max(denominator, 0.000001);

    return numberator / denominator;
}

// Geometry Function
// alpha: 表面粗糙度
// N: 法线
// X: 视线方向或者光线方向
float _G_Schlick_Beckmann_GGX(float alpha, vec3 N, vec3 X) {
    float numerator = max(dot(N, X), 0.0);

    // FIXME:
    float k = pow(alpha, 2) / 2.0;
    float denominator = max(dot(N, X), 0.0) * (1.0 - k) + k;
    denominator = max(denominator, 0.000001);

    return numerator / denominator;
}

float G(float alpha, vec3 N, vec3 V, vec3 L) {
    return _G_Schlick_Beckmann_GGX(alpha, N, V) * _G_Schlick_Beckmann_GGX(alpha, N, L);
}


// Fresnel-Schlick Function
// F0: 基础反射率，即颜色
// V: 视线向量
// H: half-way vector
vec3 F(vec3 F0, vec3 V, vec3 H) {
    return F0 + (vec3(1.0) - F0) * pow(1.0 - max(dot(V, H), 0.0), 5.0);
}

vec3 PBR(float alpha, vec3 N, vec3 V, vec3 L, vec3 H, vec3 Color) {
    vec3 Ks = F(Color, V, H);
    vec3 Kd = (vec3(1.0) - Ks) * (1.0 - metallic);

    vec3 lambert = Color / PI;

    vec3 cookTorranceNumerator = D(alpha, N, H) * G(alpha, N, V, L) * F(Color, V, H);
    float cookTorranceDenominator = 4.0 * max(dot(V, N), 0.0) * max(dot(L, N), 0.0);
    cookTorranceDenominator = max(cookTorranceDenominator, 0.000001);
    vec3 cookTorrance = cookTorranceNumerator / cookTorranceDenominator;

    vec3 BRDF = Kd * lambert + cookTorrance;
    vec3 outgoingLight = emissivityMesh + BRDF * lightColor * max(dot(L, N), 0.0);

    return outgoingLight;
}


void main()
{
    vec3 N = normalize(normal);
    vec3 V = normalize(cameraPosition - position.xyz);

    vec3 L = normalize(lightPosition - position.xyz);   // 从 fragment 指向 light
    vec3 H = normalize(V + L);                      // half-way vector

//    vec3 Color = vec3(1.0, 0.0, 0.0);
    vec3 Color = texture(albedo, texcoord).rgb;

//    FragColor = vec4(1.0);
    FragColor = vec4(PBR(roughness, N, V, L, H, Color), 1.0);
}
