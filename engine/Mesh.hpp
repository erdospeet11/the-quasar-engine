#pragma once
#include <string>
#include <vector>

#include <glm/glm.hpp>

namespace engine {
    struct Vertex {
        glm::vec3 Position;
        glm::vec3 Normal;
        glm::vec2 TexCoords;
        glm::vec3 Tangent;
        glm::vec3 Bitangent;
    };

    struct Texture {
        unsigned int id;
        std::string type;
        std::string path;
    };

    class Mesh {
    public:
        std::vector<Vertex>       vertices;
        std::vector<unsigned int> indices;
        std::vector<Texture>      textures;

        Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture> textures);
        ~Mesh() = default;

        void Draw(unsigned int shaderProgram);
        unsigned int VAO;
    private:
        unsigned int VBO, EBO;
        void setupMesh();
    };
}