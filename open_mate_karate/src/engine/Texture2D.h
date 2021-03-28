#ifndef TEXTURE2D_H
#define TEXTURE2D_H

#include <glew.h>
#include <string>

class Texture2D
{
public:
    Texture2D();
    virtual ~Texture2D();

    bool loadTexture(const std::string& filename, bool generateMipmaps = true);
    void bind(GLuint texUnit = 0);
    void unbind(GLuint texUnit = 0);

private:

    GLuint texture;
};

#endif // TEXTURE2D_H