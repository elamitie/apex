#pragma once

/*
 *  Mesh implementation loosely based off of LearnOpenGL.com and Glitter (https://github.com/Polytonic/Glitter)
 *  Slightly modified Nanosuit body (from crytek) obtained from LearnOpenGL.com
 */

#include <GL/glew.h>
#include <vector>

#include "../../utils/Types.h"
#include "../assets/Shader.h"
#include "../assets/Texture.h"
#include "Vertex.h"
#include "MaterialBase.h"

#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
#include <assimp/scene.h>

#include <map>

class Mesh {
public:
	Mesh() {};
    Mesh(const std::string& filename);
    Mesh(const std::vector<Vertex>& vertices,
         const std::vector<uint>& indices,
         const std::vector<TexturePtr>& textures,
         const std::string& name = "");
    virtual ~Mesh();

    virtual void Render(MaterialBase* mat);

private:
    void Parse(const std::string& path, const aiNode* node, const aiScene* scene);
    void Parse(const std::string& path, const aiMesh* mesh, const aiScene* scene);
    std::vector<TexturePtr> Process(const std::string& path,
                                    aiMaterial* material,
                                    aiTextureType type);

protected:
    std::vector<MeshPtr> mChildren;
    std::vector<uint> mIndices;
    std::vector<Vertex> mVertices;
    std::vector<TexturePtr> mTextures;

    GLuint mVertexArray;
    GLuint mVertexBuffer;
    GLuint mIndexBuffer;

    std::string mName;
};