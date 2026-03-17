#pragma once
#include <glm/glm.hpp>

namespace engine {
    class Model;
    class Renderer{
        private:
            unsigned int shaderProgram;
            unsigned int VAO, VBO, EBO;
            void initCube();
        public:
            Renderer();
            ~Renderer();
            
            void clear();
            void renderCube();
            void renderModel(Model& model, const glm::mat4& transform);
    };
}