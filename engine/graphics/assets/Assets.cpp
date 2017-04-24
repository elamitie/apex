#include "Assets.h"

#include "graphics/assets/Texture.h"
#include "graphics/assets/Shader.h"
#include "graphics/assets/Cubemap.h"
#include "graphics/mesh/Mesh.h"
#include "graphics/mesh/MaterialBase.h"

#include "utils/FileSystem.h"

Assets& Assets::Instance()
{
	static Assets* instance = new Assets();
	return *instance;
}

void Assets::RegisterAssetsFromFile(const std::string & file)
{
}

Texture2D* Assets::GetTexture(const std::string & name)
{
	auto it = mTextures.find(name);

	// Contingency incase file did not contain this texture.
	if (it == mTextures.end())
	{
		// TODO: Parse out the file name from the containing folder
		// e.g. "pbr/plastic/albedo.png" -> "plastic_albedo"
		// Do the same for environments?
		Texture2D* tmp = new Texture2D();
		tmp->Load(FileSystem::GetPath("resources/textures/" + name));
		mTextures.insert(std::make_pair(name, tmp));

		return tmp;
	}

	return it->second;
}

Shader* Assets::GetShader(const std::string & name)
{
	auto it = mShaders.find(name);

	// TODO: Contingency for this requires funky name shenanigans
	// to parse out the ".vert" and ".frag"

	return it->second;
}

Mesh* Assets::GetMesh(const std::string & name)
{
	auto it = mMeshes.find(name);

	if (it == mMeshes.end())
	{
		// TODO: Parse out the file name from the containing folder
		// e.g. "nanosuit/nanosuit.obj" -> "nanosuit"
		// consider also just tracking by directory instead of by actual obj name
		// for mtl files
	}

	return it->second;
}

MaterialBase* Assets::GetMaterial(const std::string & name)
{
	auto it = mMaterials.find(name);

	if (it == mMaterials.end())
	{
		// TODO: Loading should be different and better planned since they rely on
		// different textures and / or values. Consider not having a contingency for
		// Materials
	}

	return it->second;
}

Cubemap* Assets::GetCubemap(const std::string & name)
{
	auto it = mCubemaps.find(name);

	if (it == mCubemaps.end())
	{

	}

	return it->second;
}

void Assets::LoadTexture(const std::string & name)
{
}

void Assets::LoadShader(const std::string & name)
{
}

void Assets::LoadMesh(const std::string & name)
{
}

void Assets::LoadMaterial(const std::string & name)
{
}

void Assets::LoadCubemap(const std::string & name)
{
}
