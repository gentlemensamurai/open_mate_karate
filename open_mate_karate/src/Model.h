#ifndef MODEL_H
#define MODEL_H

#include "ShaderProgram.h"
#include "Mesh.h"
#include "Texture2D.h"
#include "Material.h"

class Model
{
public:
    Model
    (
        Material* material,
        Texture2D* diffuseTexture,
        Texture2D* specularTexture,
        std::vector<Mesh*> meshes,
        glm::vec3 position,
        glm::vec3 rotation,
        glm::vec3 scale
    );
    ~Model();

    void update();
    void render(ShaderProgram& shader);

private:
    Material* material;
    Texture2D* diffuseTexture;
    Texture2D* specularTexture;

    std::vector<Mesh*> meshes;

    glm::vec3 position;
    glm::vec3 rotation;
    glm::vec3 scale;

    void updateUniforms();
};

#endif // MODEL_H