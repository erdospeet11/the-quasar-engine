#pragma once

namespace engine {
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
    };
}