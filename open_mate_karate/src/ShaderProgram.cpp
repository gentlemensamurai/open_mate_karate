#include "ShaderProgram.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <gtc/type_ptr.hpp>

ShaderProgram::ShaderProgram()
    : handle(0)
{

}

ShaderProgram::~ShaderProgram()
{
    glDeleteProgram(handle);
}

bool ShaderProgram::loadShaders(const std::string& vertShaderFilename, const std::string& fragShaderFilename)
{
    std::string vertShaderString = fileToString(vertShaderFilename);
    std::string fragShaderString = fileToString(fragShaderFilename);

    const GLchar* vertShaderSrc = vertShaderString.c_str();
    const GLchar* fragShaderSrc = fragShaderString.c_str();

    GLuint vertShader { glCreateShader(GL_VERTEX_SHADER) };
    GLuint fragShader { glCreateShader(GL_FRAGMENT_SHADER) };

    glShaderSource(vertShader, 1, &vertShaderSrc, nullptr);
    glShaderSource(fragShader, 1, &fragShaderSrc, nullptr);

    glCompileShader(vertShader);
    checkCompileErrors(vertShader, VERTEX);

    glCompileShader(fragShader);
    checkCompileErrors(fragShader, FRAGMENT);

    handle = glCreateProgram();

    glAttachShader(handle, vertShader);
    glAttachShader(handle, fragShader);
    glLinkProgram(handle);

    checkCompileErrors(handle, PROGRAM);

    uniformLocations.clear();

    glDeleteShader(vertShader);
    glDeleteShader(fragShader);

    return true;
}

void ShaderProgram::use()
{
    if (handle > 0)
    {
        glUseProgram(handle);
    }
}

void ShaderProgram::setUniform(const GLchar* name, const glm::vec2& v)
{
    GLint loc { getUniformLocation(name) };
    glUniform2f(loc, v.x, v.y);
}

void ShaderProgram::setUniform(const GLchar* name, const glm::vec3& v)
{
    GLint loc { getUniformLocation(name) };
    glUniform3f(loc, v.x, v.y, v.z);
}

void ShaderProgram::setUniform(const GLchar* name, const glm::vec4& v)
{
    GLint loc { getUniformLocation(name) };
    glUniform4f(loc, v.x, v.y, v.z, v.w);
}

void ShaderProgram::setUniform(const GLchar* name, const glm::mat4& m)
{
    GLint loc { getUniformLocation(name) };
    glUniformMatrix4fv(loc, 1, GL_FALSE, glm::value_ptr(m));
}

void ShaderProgram::setUniform(const GLchar* name, const GLfloat f)
{
    GLint loc { getUniformLocation(name) };
    glUniform1f(loc, f);
}

void ShaderProgram::setUniform(const GLchar* name, const GLint i)
{
    GLint loc { getUniformLocation(name) };
    glUniform1i(loc, i);
}

void ShaderProgram::setUniformSampler(const GLchar* name, const GLint& slot)
{
    glActiveTexture(GL_TEXTURE0 + slot);
    GLint loc { getUniformLocation(name) };
    glUniform1i(loc, slot);
}

GLuint ShaderProgram::getProgram() const
{
    return handle;
}

std::string ShaderProgram::fileToString(const std::string& filename)
{
    std::stringstream ss;
    std::ifstream file;

    try
    {
        file.open(filename, std::ios::in);

        if (!file.fail())
        {
            ss << file.rdbuf();
        }

        file.close();
    }
    catch (std::exception e)
    {
        std::cerr << "Error reading shader filename!" << std::endl;
    }

    return ss.str();
}

void ShaderProgram::checkCompileErrors(GLuint shader, ShaderType type)
{
    int status { 0 };

    if (type == PROGRAM)
    {
        glGetProgramiv(handle, GL_LINK_STATUS, &status);

        if (status == GL_FALSE)
        {
            GLint length { 0 };

            glGetProgramiv(handle, GL_INFO_LOG_LENGTH, &length);

            std::string errorLog(length, ' ');

            glGetProgramInfoLog(handle, length, &length, &errorLog[0]);

            std::cerr << "Error! Program failed to link! " << errorLog << std::endl;
        }
    }
    else if (type == VERTEX || type == FRAGMENT)
    {
        glGetShaderiv(shader, GL_COMPILE_STATUS, &status);

        if (status == GL_FALSE)
        {
            GLint length { 0 };

            glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &length);

            std::string errorLog(length, ' ');

            glGetShaderInfoLog(shader, length, &length, &errorLog[0]);

            std::cerr << "Error! Shader failed to compile! " << errorLog << std::endl;
        }
    }
}

GLint ShaderProgram::getUniformLocation(const GLchar* name)
{
    std::map<std::string, GLint>::iterator it { uniformLocations.find(name) };

    if (it == uniformLocations.end())
    {
        uniformLocations[name] = glGetUniformLocation(handle, name);
    }

    return uniformLocations[name];
}