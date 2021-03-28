#version 330 core

struct Material
{
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    sampler2D diffuseMap;
    sampler2D specularMap;
    float shininess;
};

struct DirLight
{
    vec3 dir;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

in vec2 TexCoord;
in vec3 Normal;
in vec3 FragPos;

uniform DirLight light;
uniform Material material;
uniform vec3 viewPos;

out vec4 fragColor;

void main()
{
    // AMBIENT
    vec3 ambient = light.ambient * material.ambient * vec3(texture(material.diffuseMap, TexCoord));

    // DIFFUSE
    vec3 normal = normalize(Normal);
    vec3 lightDir = normalize(-light.dir);
    float normalDotLight = max(dot(normal, lightDir), 0.0f);
    vec3 diffuse = light.diffuse * vec3(texture(material.diffuseMap, TexCoord)) * normalDotLight;

    // SPECULAR
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 halfDir = normalize(lightDir + viewDir);
    float normalDotHalf = max(dot(normal, halfDir), 0.0f);
    vec3 specular = light.specular * material.specular * pow(normalDotHalf, material.shininess);

    fragColor = vec4(ambient + diffuse + specular, 1.0f);
}