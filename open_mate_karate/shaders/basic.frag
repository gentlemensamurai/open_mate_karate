#version 330 core

in vec2 TexCoord;
in vec3 Normal;
in vec3 FragPos;

uniform sampler2D tex;
uniform vec3 lightColor;
uniform vec3 lightPos;
uniform vec3 viewPos;

out vec4 fragColor;

void main()
{
    // AMBIENT
    float ambientFactor = 0.1f;
    vec3 ambient = lightColor * ambientFactor;

    // DIFFUSE
    vec3 normal = normalize(Normal);
    vec3 lightDir = normalize(lightPos - FragPos);
    float normalDotLight = max(dot(normal, lightDir), 0.0f);
    vec3 diffuse = lightColor * normalDotLight;

    // SPECULAR
    float specularFactor = 0.8f;
    float shininess = 100.0f;
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectionDir = reflect(-lightDir, normal);
    float reflectionDotView = max(dot(reflectionDir, viewDir), 0.0f);
    vec3 specular = lightColor * specularFactor * pow(reflectionDotView, shininess);

    vec4 texel = texture(tex, TexCoord);
    fragColor = vec4(ambient + diffuse + specular, 1.0f) * texel;
}