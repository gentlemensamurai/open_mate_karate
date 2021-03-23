#ifndef SHADER_PROGRAM_H
#define SHADER_PROGRAM_H

#include <string>
#include <map>
#include <glew.h>
#include <glm.hpp>

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

    void setUniform(const GLchar* name, const glm::vec2& v);
    void setUniform(const GLchar* name, const glm::vec3& v);
    void setUniform(const GLchar* name, const glm::vec4& v);
    void setUniform(const GLchar* name, const glm::mat4& m);
    void setUniform(const GLchar* name, const GLfloat& f);
    void setUniformSampler(const GLchar* name, const GLint& slot);

    GLuint getProgram() const;

private:

    GLuint handle;
    std::map<std::string, GLint> uniformLocations;

    std::string fileToString(const std::string& filename);
    void checkCompileErrors(GLuint shader, ShaderType type);
    GLint getUniformLocation(const GLchar* name);
};

#endif // SHADER_PROGRAM_H