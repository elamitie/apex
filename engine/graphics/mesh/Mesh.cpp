#include "Mesh.h"
#include "utils/Logger.h"

Mesh::Mesh(const std::string& filename) {
    Assimp::Importer loader;
    uint flags = aiProcessPreset_TargetRealtime_MaxQuality |
                 aiProcess_OptimizeGraph |
                 aiProcess_CalcTangentSpace |
                 aiProcess_FlipUVs;

    std::string path = FileSystem::GetPath("resources/models/" + filename);
    const aiScene* scene = loader.ReadFile(path, flags);
    if (!scene)
        printf("%s\n", loader.GetErrorString());

    size_t index = path.find_last_of("/");

    parse(path.substr(0, index), scene->mRootNode, scene);
}

Mesh::Mesh(const std::vector<Vertex>& vertices,
           const std::vector<uint>& indices,
           const std::vector<TexturePtr>& textures,
           const std::string& name) {

    mVertices = vertices;
    mIndices = indices;
    mTextures = textures;
    // This will be nice to track for the future
    mName = name;

    glGenVertexArrays(1, &mVertexArray);
    glBindVertexArray(mVertexArray);

    glGenBuffers(1, &mVertexBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, mVertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, mVertices.size() * sizeof(Vertex),
                 &mVertices.front(), GL_STATIC_DRAW);

    glGenBuffers(1, &mIndexBuffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mIndexBuffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, mIndices.size() * sizeof(GLuint),
                 &mIndices.front(), GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, Position));
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, Normal));
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, TexCoords));
    glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, Tangents));
    glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, Bitangents));
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(2);
    glEnableVertexAttribArray(3);
    glEnableVertexAttribArray(4);

    glBindVertexArray(0);
    glDeleteBuffers(1, &mVertexBuffer);
    glDeleteBuffers(1, &mIndexBuffer);
}

Mesh::~Mesh() {
    glDeleteVertexArrays(1, &mVertexArray);
}

void Mesh::render(ShaderPtr shader) {

    // TODO: MAKE THIS CLEANER WITH MATERIAL ABSTRACTION

    uint loc, diff, spec, norm;
    loc = diff = spec = 0;

    for (auto& mesh : mChildren)
        mesh->render(shader);

    for (auto& texture : mTextures) {
        TextureType t = texture->mType;
        std::string uniformTexture = TextureTypeStr[t];

        if (uniformTexture == "diffuse")
            uniformTexture += (++diff > 0) ? std::to_string(diff) : "";
        else if (uniformTexture == "specular")
            uniformTexture += (++spec > 0) ? std::to_string(spec) : "";
        else if (uniformTexture == "normal")
            uniformTexture += (++norm > 0) ? std::to_string(spec) : "";

        texture->bind(loc);
        shader->SetUniform("material." + uniformTexture, (GLint)loc++);
    }

    glBindVertexArray(mVertexArray);
    glDrawElements(GL_TRIANGLES, mIndices.size(), GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}

void Mesh::parse(const std::string& path, const aiNode* node, const aiScene* scene) {
    for (int i = 0; i < node->mNumMeshes; i++)
        parse(path, scene->mMeshes[node->mMeshes[i]], scene);
    for (int i = 0; i < node->mNumChildren; i++)
        parse(path, node->mChildren[i], scene);
}

void Mesh::parse(const std::string& path, const aiMesh* mesh, const aiScene* scene) {
    std::vector<Vertex> vertices;
    for (int i = 0; i < mesh->mNumVertices; i++) {
        Vertex vertex;
        if (mesh->mTextureCoords[0]) {
            glm::vec3 vec3;
            glm::vec2 vec2;

            vec3.x = mesh->mVertices[i].x;
            vec3.y = mesh->mVertices[i].y;
            vec3.z = mesh->mVertices[i].z;
            vertex.Position = vec3;

            vec3.x = mesh->mNormals[i].x;
            vec3.y = mesh->mNormals[i].y;
            vec3.z = mesh->mNormals[i].z;
            vertex.Normal = vec3;

            vec2.x = mesh->mTextureCoords[0][i].x;
            vec2.y = mesh->mTextureCoords[0][i].y;
            vertex.TexCoords = vec2;

            vec3.x = mesh->mTangents[i].x;
            vec3.y = mesh->mTangents[i].y;
            vec3.z = mesh->mTangents[i].z;
            vertex.Tangents = vec3;

            vec3.x = mesh->mBitangents[i].x;
            vec3.y = mesh->mBitangents[i].y;
            vec3.z = mesh->mBitangents[i].z;
            vertex.Bitangents = vec3;

            vertices.push_back(vertex);
        }
    }

    std::vector<uint> indices;
    for (int i = 0; i < mesh->mNumFaces; i++)
        for (int j = 0; j < mesh->mFaces[i].mNumIndices; j++)
            indices.push_back(mesh->mFaces[i].mIndices[j]);

    // TODO: Process any materials

    std::vector<TexturePtr> textures;
    std::vector<TexturePtr> diffuse  = process(path, scene->mMaterials[mesh->mMaterialIndex],
                                       aiTextureType_DIFFUSE);
    std::vector<TexturePtr> specular = process(path, scene->mMaterials[mesh->mMaterialIndex],
                                       aiTextureType_SPECULAR);

    textures.insert(textures.end(), diffuse.begin(), diffuse.end());
    textures.insert(textures.end(), specular.begin(), specular.end());

    std::string name = mesh->mName.C_Str();
    mChildren.push_back(std::make_shared<Mesh>(vertices, indices, textures, name));
}

std::vector<TexturePtr> Mesh::process(const std::string& path, aiMaterial* material,
                                      aiTextureType type) {
    std::vector<TexturePtr> textures;
    for (int i = 0; i < material->GetTextureCount(type); i++) {
        aiString str;
        material->GetTexture(type, i, &str);
        std::string filename = str.C_Str();
        filename = path + "/" + filename;

        TexturePtr texture = std::make_shared<Texture2D>();
        texture->load(filename);

        if (type == aiTextureType_DIFFUSE)  texture->mType = TextureType::DIFFUSE;
        if (type == aiTextureType_SPECULAR) texture->mType = TextureType::SPECULAR;

        textures.push_back(texture);
    }

    return textures;
}