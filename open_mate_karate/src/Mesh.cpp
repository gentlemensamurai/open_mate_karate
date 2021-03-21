#include "Mesh.h"
#include <iostream>
#include <sstream>
#include <fstream>

Mesh::Mesh()
    : loaded(false)
{

}

Mesh::~Mesh()
{
    glDeleteVertexArrays(1, &vao);
    glDeleteBuffers(1, &vbo);
}

bool Mesh::loadObj(const std::string& filename)
{
    std::vector<unsigned int> posIndices;
    std::vector<unsigned int> texCoordIndices;
    std::vector<glm::vec3> tempPos;
    std::vector<glm::vec2> tempTexCoord;

    if (filename.find(".obj") != std::string::npos)
    {
        std::ifstream file(filename, std::ios::in);

        if (!file)
        {
            std::cerr << "Cannot open " << filename << "!" << std::endl;
            return false;
        }

        std::cout << "Loading .obj file " << filename << "..." << std::endl;

        std::string lineBuffer;

        while (std::getline(file, lineBuffer))
        {
            if (lineBuffer.substr(0, 2) == "v ")
            {
                std::istringstream posString(lineBuffer.substr(2));
                glm::vec3 pos;
                posString >> pos.x;
                posString >> pos.y;
                posString >> pos.z;
                tempPos.push_back(pos);
            }
            else if (lineBuffer.substr(0, 2) == "vt")
            {
                std::istringstream texCoordString(lineBuffer.substr(3));
                glm::vec2 texCoord;
                texCoordString >> texCoord.s;
                texCoordString >> texCoord.t;
                tempTexCoord.push_back(texCoord);
            }
            else if (lineBuffer.substr(0, 2) == "f ")
            {
                int p1 { 0 };
                int p2 { 0 };
                int p3 { 0 };
                int t1 { 0 };
                int t2 { 0 };
                int t3 { 0 };
                int n1 { 0 };
                int n2 { 0 };
                int n3 { 0 };
                const char* face { lineBuffer.c_str() };
                int match { sscanf_s(face, "f %i/%i/%i %i/%i/%i %i/%i/%i", &p1, &t1, &n1, &p2, &t2, &n2, &p3, &t3, &n3) };

                if (match != 9)
                {
                    std::cerr << "Failed to parse .obj file!" << std::endl;
                    return false;
                }

                posIndices.push_back(p1);
                posIndices.push_back(p2);
                posIndices.push_back(p3);
                texCoordIndices.push_back(t1);
                texCoordIndices.push_back(t2);
                texCoordIndices.push_back(t3);
            }
        }

        file.close();

        for (size_t i { 0 }; i < posIndices.size(); i++)
        {
            Vertex vertex;
            vertex.pos = tempPos[posIndices[i] - 1];
            vertex.texCoord = tempTexCoord[texCoordIndices[i] - 1];
            vertices.push_back(vertex);
        }

        initBuffers();

        return (loaded = true);
    }

    return false;
}

void Mesh::draw()
{
    if (!loaded) return;

    glBindVertexArray(vao);
    glDrawArrays(GL_TRIANGLES, 0, vertices.size());
    glBindVertexArray(0);
}

void Mesh::initBuffers()
{
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);

    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    // POSITION
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), nullptr);
    glEnableVertexAttribArray(0);

    // TEXTURE COORDINATES
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (const void*)(3 * sizeof(GLfloat)));
    glEnableVertexAttribArray(1);

    glBindVertexArray(0);
}