#version 330 core

in vec2 TexCoord;
in vec3 Normal;
in vec3 FragPos;

uniform sampler2D tex;
uniform vec3 lightColor;
uniform vec3 lightPos;

out vec4 fragColor;

void main()
{
    // AMBIENT
    float ambientFactor = 0.25f;
    vec3 ambient = lightColor * ambientFactor;

    // DIFFUSE
    vec3 normal = normalize(Normal);
    vec3 lightDir = normalize(lightPos - FragPos);
    float normalDotLight = max(dot(normal, lightDir), 0.0f);
    vec3 diffuse = lightColor * normalDotLight;

    // SPECULAR
    vec3 specular = vec3(0.0f);

    vec4 texel = texture(tex, TexCoord);
    fragColor = vec4(ambient + diffuse + specular, 1.0) * texel;
}