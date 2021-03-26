#version 330 core

struct Material
{
    vec3 ambient;
    sampler2D diffuseMap;
    vec3 specular;
    float shininess;
};

struct PointLight
{
    vec3 position;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    float constant;
    float linear;
    float exponent;
};

in vec2 TexCoord;
in vec3 Normal;
in vec3 FragPos;

uniform PointLight light;
uniform Material material;
uniform vec3 viewPos;

out vec4 fragColor;

void main()
{
    // AMBIENT
    vec3 ambient = light.ambient * material.ambient * vec3(texture(material.diffuseMap, TexCoord));

    // DIFFUSE
    vec3 normal = normalize(Normal);
    vec3 lightDir = normalize(light.position - FragPos);
    float normalDotLight = max(dot(normal, lightDir), 0.0f);
    vec3 diffuse = light.diffuse * vec3(texture(material.diffuseMap, TexCoord)) * normalDotLight;

    // SPECULAR
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 halfDir = normalize(lightDir + viewDir);
    float normalDotHalf = max(dot(normal, halfDir), 0.0f);
    vec3 specular = light.specular * material.specular * pow(normalDotHalf, material.shininess);

    float dist = length(light.position - FragPos);
    float attenuation = 1.0f / (light.constant + light.linear * dist + light.exponent * (dist * dist));
    diffuse *= attenuation;
    specular *= attenuation;

    fragColor = vec4(ambient + diffuse + specular, 1.0f);
}