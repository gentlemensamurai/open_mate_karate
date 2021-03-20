#version 330 core

in vec2 TexCoord;
out vec4 fragColor;
uniform sampler2D tex_0;
uniform sampler2D tex_1;

void main()
{
    fragColor = mix(texture(tex_0, TexCoord), texture(tex_1, TexCoord), 0.5);
}