#ifndef MATERIAL_H
#define MATERIAL_H

#include <glew.h>
#include <glm.hpp>
#include <vec2.hpp>
#include <vec3.hpp>
#include "ShaderProgram.h"

class Material
{
public:
    Material
    (
        glm::vec3 ambient,
        glm::vec3 diffuse,
        glm::vec3 specular,
        GLint diffuseMap,
        GLint specularMap,
        float shininess
    );
    ~Material();

    void sentToShader(ShaderProgram& shader);

private:
    glm::vec3 ambient;
    glm::vec3 diffuse;
    glm::vec3 specular;
    GLint diffuseMap;
    GLint specularMap;
    float shininess;
};

#endif MATERIAL_H