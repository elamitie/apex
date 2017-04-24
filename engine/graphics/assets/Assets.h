#pragma once

#include <string>
#include <map>

class MaterialBase;
class Mesh;
class Shader;
class Texture2D;
class Cubemap;

// Asset management, storage and loading.
class Assets
{
public:
	static Assets& Instance();

	void RegisterAssetsFromFile(const std::string& file);

	Texture2D*    GetTexture(const std::string& name);
	Shader*       GetShader(const std::string& name);
	Mesh*         GetMesh(const std::string& name);
	MaterialBase* GetMaterial(const std::string& name);
	Cubemap*      GetCubemap(const std::string& name);

private:
	Assets() {};
	~Assets() {};

	void LoadTexture(const std::string& name);
	void LoadShader(const std::string& name);
	void LoadMesh(const std::string& name);
	void LoadMaterial(const std::string& name);
	void LoadCubemap(const std::string& name);

	std::map<std::string, Texture2D*> mTextures;
	std::map<std::string, Shader*> mShaders;
	std::map<std::string, Mesh*> mMeshes;
	std::map<std::string, MaterialBase*> mMaterials;
	std::map<std::string, Cubemap*> mCubemaps;
};