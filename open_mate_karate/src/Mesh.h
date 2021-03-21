#ifndef MESH_H
#define MESH_H

#include <string>
#include <vector>
#include <glew.h>
#include <glm.hpp>

struct Vertex
{
    glm::vec3 pos;
    glm::vec2 texCoord;
};

class Mesh
{
public:
    Mesh();
    ~Mesh();

    bool loadObj(const std::string& filename);
    void draw();

private:
    bool loaded;
    std::vector<Vertex> vertices;
    GLuint vbo;
    GLuint vao;

    void initBuffers();
};

#endif // MESH_H