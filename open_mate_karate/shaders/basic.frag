#version 330 core

uniform vec4 vertColor;
out vec4 fragColor;

void main()
{
    fragColor = vertColor;
}