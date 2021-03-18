#include "Texture2D.h"
#include <iostream>
#include <stb_image.h>

Texture2D::Texture2D()
    : texture(0)
{

}
Texture2D::~Texture2D()
{

}

bool Texture2D::loadTexture(const std::string& filename, bool generateMipmaps)
{
    int width { 0 };
    int height { 0 };
    int components { 0 };
    unsigned char* imageData { stbi_load(filename.c_str(), &width, &height, &components, STBI_rgb_alpha) };

    if (imageData == nullptr)
    {
        std::cerr << "Error loading texture " << filename << "!" << std::endl;
        return false;
    }

    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, imageData);

    if (generateMipmaps)
    {
        glGenerateMipmap(GL_TEXTURE_2D);
    }

    stbi_image_free(imageData);
    glBindTexture(GL_TEXTURE_2D, 0);

    return true;
}

void Texture2D::bind(GLuint textureUnit)
{
    glBindTexture(GL_TEXTURE_2D, texture);
}