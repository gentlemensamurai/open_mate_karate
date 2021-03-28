#include "Model.h"

Model::Model
(
    Material* material,
    Texture2D* diffuseTexture,
    Texture2D* specularTexture,
    std::vector<Mesh*> meshes,
    glm::vec3 position,
    glm::vec3 rotation,
    glm::vec3 scale
)
    : material(material),
      diffuseTexture(diffuseTexture),
      specularTexture(specularTexture),
      meshes(meshes),
      position(position),
      rotation(rotation),
      scale(scale)
{

}

Model::~Model()
{

}

void Model::update()
{

}

void Model::render(ShaderProgram& shader)
{
    updateUniforms();
    material->sendToShader(shader);
    shader.use();
    diffuseTexture->bind(0);
    specularTexture->bind(1);

    for (size_t i { 0 }; i < meshes.size(); i++)
    {
        meshes[i]->draw();
    }

    diffuseTexture->unbind(0);
    specularTexture->unbind(1);
}

void Model::updateUniforms()
{

}