#pragma once

#include "mesh.h"
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

class Model
{
public:
	Model(const std::string& path);
	~Model();

	void Render(Shader* shader);

private:
	std::vector<Mesh> mMeshes;
	std::string mDirectory;

private:
	void Load(const std::string& path);
	void ProcessNode(aiNode* node, const aiScene* scene);
	Mesh ProcessMesh(aiMesh* mesh, const aiScene* scene);
	std::vector<Texture2D*> LoadMaterialTextures(aiMaterial* mat, aiTextureType type, std::string typeName);
};