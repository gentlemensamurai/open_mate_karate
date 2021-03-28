#include "Material.h"

Material::Material
(
    glm::vec3 ambient,
    glm::vec3 diffuse,
    glm::vec3 specular,
    GLint diffuseMap,
    GLint specularMap,
    float shininess
)
    : ambient(ambient),
      diffuse(diffuse),
      specular(specular),
      diffuseMap(diffuseMap),
      specularMap(specularMap),
      shininess(shininess)
{

}

Material::~Material()
{

}

void Material::sendToShader(ShaderProgram& shader)
{
    shader.setUniform("material.ambient", ambient);
    shader.setUniform("material.diffuse", diffuse);
    shader.setUniform("material.specular", specular);
    shader.setUniform("material.diffuseMap", diffuseMap);
    shader.setUniform("material.specularMap", specularMap);
    shader.setUniform("material.shininess", shininess);
}