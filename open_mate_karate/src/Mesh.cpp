#include "Mesh.h"
#include <iostream>
#include <sstream>
#include <fstream>

std::vector<std::string> split(std::string string, std::string character)
{
    std::vector<std::string> result;

    while (1)
    {
        int pos = string.find(character);

        if (pos == -1)
        {
            result.push_back(string);
            break;
        }

        result.push_back(string.substr(0, pos));
        string = string.substr(pos + 1, string.size() - pos - 1);
    }

    return result;
}

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
    std::vector<unsigned int> normalIndices;
    std::vector<glm::vec3> tempPos;
    std::vector<glm::vec2> tempTexCoord;
    std::vector<glm::vec3> tempNormals;

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
            std::stringstream ss(lineBuffer);
            std::string cmd;
            ss >> cmd;

            if (cmd == "v")
            {
                glm::vec3 pos;
                int dim { 0 };

                while (dim < 3 && ss >> pos[dim])
                {
                    dim++;
                }

                tempPos.push_back(pos);
            }
            else if (cmd == "vt")
            {
                glm::vec2 texCoord;
                int dim { 0 };

                while (dim < 2 && ss >> texCoord[dim])
                {
                    dim++;
                }

                tempTexCoord.push_back(texCoord);
            }
            else if (cmd == "vn")
            {
                glm::vec3 normal;
                int dim { 0 };

                while (dim < 3 && ss >> normal[dim])
                {
                    dim++;
                }
                normal = glm::normalize(normal);
                tempNormals.push_back(normal);
            }
            else if (cmd == "f")
            {
                std::string faceData;
                int posIndex { 0 };
                int texCoordIndex { 0 };
                int normalIndex { 0 };

                while (ss >> faceData)
                {
                    std::vector<std::string> data = split(faceData, "/");

                    if (data[0].size() > 0)
                    {
                        sscanf_s(data[0].c_str(), "%i", &posIndex);
                        posIndices.push_back(posIndex);
                    }

                    if (data.size() >= 1)
                    {
                        if (data[1].size() > 0)
                        {
                            sscanf_s(data[1].c_str(), "%i", &texCoordIndex);
                            texCoordIndices.push_back(texCoordIndex);
                        }
                    }

                    if (data.size() >= 2)
                    {
                        if (data[2].size() > 0)
                        {
                            sscanf_s(data[2].c_str(), "%i", &normalIndex);
                            normalIndices.push_back(normalIndex);
                        }
                    }
                }
            }
        }

        file.close();

        for (size_t i { 0 }; i < posIndices.size(); i++)
        {
            Vertex vertex;

            if (tempPos.size() > 0)
            {
                vertex.pos = tempPos[posIndices[i] - 1];
            }

            if (tempNormals.size() > 0)
            {
                vertex.normal = tempNormals[normalIndices[i] - 1];
            }

            if (tempTexCoord.size() > 0)
            {
                vertex.texCoord = tempTexCoord[texCoordIndices[i] - 1];
            }

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
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), nullptr);
    glEnableVertexAttribArray(0);

    // NORMALS
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void*)(3 * sizeof(GLfloat)));
    glEnableVertexAttribArray(1);

    // TEXTURE COORDINATES
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void*)(6 * sizeof(GLfloat)));
    glEnableVertexAttribArray(2);

    glBindVertexArray(0);
}