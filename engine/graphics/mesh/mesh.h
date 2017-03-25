#pragma once

/*
 *  Mesh implementation loosely based off of LearnOpenGL.com and Glitter (https://github.com/Polytonic/Glitter)
 *  Slightly modified Nanosuit body (from crytek) obtained from LearnOpenGL.com
 */

#include <GL/glew.h>
#include <vector>

#include "../../utils/types.h"
#include "../assets/shader.h"
#include "../assets/texture.h"
#include "vertex.h"

#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
#include <assimp/scene.h>

#include <map>

class Mesh {
public:
    Mesh(const std::string& filename);
    Mesh(const std::vector<Vertex>& vertices,
         const std::vector<uint>& indices,
         const std::vector<TexturePtr>& textures,
         const std::string& name = "");
    ~Mesh();

    void render(ShaderPtr shader);

private:
    void parse(const std::string& path, const aiNode* node, const aiScene* scene);
    void parse(const std::string& path, const aiMesh* mesh, const aiScene* scene);
    std::vector<TexturePtr> process(const std::string& path,
                                    aiMaterial* material,
                                    aiTextureType type);

private:
    std::vector<MeshPtr> mChildren;
    std::vector<uint> mIndices;
    std::vector<Vertex> mVertices;
    std::vector<TexturePtr> mTextures;

    GLuint mVertexArray;
    GLuint mVertexBuffer;
    GLuint mIndexBuffer;

    std::string mName;
};