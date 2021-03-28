#include "Model.h"
#include <gtc/matrix_transform.hpp>

Model::Model
(
    Material* material,
    Texture2D* diffuseTexture,
    Texture2D* specularTexture,
    Mesh* mesh,
    glm::vec3 position,
    glm::vec3 rotation,
    glm::vec3 scale
)
    : material(material),
      diffuseTexture(diffuseTexture),
      specularTexture(specularTexture),
      mesh(mesh),
      position(position),
      rotation(rotation),
      scale(scale),
      model(1.0f)
{

}

Model::~Model()
{

}

void Model::update()
{
    model = glm::translate(glm::mat4(1.0f), position) * glm::scale(glm::mat4(1.0f), scale);
}

void Model::render(ShaderProgram& shader)
{
    updateUniforms(shader);
    material->sendToShader(shader);
    shader.use();
    diffuseTexture->bind(0);
    specularTexture->bind(1);
    mesh->draw();
    diffuseTexture->unbind(0);
    specularTexture->unbind(1);
}

void Model::updateUniforms(ShaderProgram& shader)
{
    shader.setUniform("model", model);
}