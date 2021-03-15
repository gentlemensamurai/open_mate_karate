#ifndef SHADER_PROGRAM_H
#define SHADER_PROGRAM_H

#include <string>
#include <glew.h>

class ShaderProgram
{
public:

    enum ShaderType
    {
        VERTEX = 0,
        FRAGMENT,
        PROGRAM
    };

    ShaderProgram();
    ~ShaderProgram();

    bool loadShaders(const std::string& vertShaderFilename, const std::string& fragShaderFilename);
    void use();

private:

    GLuint handle;

    std::string fileToString(const std::string& filename);
    void checkCompileErrors(GLuint shader, ShaderType type);

};

#endif // SHADER_PROGRAM_H