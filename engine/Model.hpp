#pragma once
#include "Mesh.hpp"
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <string>
#include <vector>

namespace engine {
    class Model {
    public:
        std::vector<Texture> textures_loaded;
        std::vector<Mesh>    meshes;
        std::string directory;
        bool gammaCorrection;
        Model(std::string const &path, bool gamma = false);
        void Draw(unsigned int shaderProgram);
    private:
        void loadModel(std::string const &path);
        void processNode(aiNode *node, const aiScene *scene);
        Mesh processMesh(aiMesh *mesh, const aiScene *scene);
        std::vector<Texture> loadMaterialTextures(aiMaterial *mat, aiTextureType type, std::string typeName);
    };
}
