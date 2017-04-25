#include "Assets.h"

#include "graphics/assets/Texture.h"
#include "graphics/assets/Shader.h"
#include "graphics/assets/Cubemap.h"
#include "graphics/mesh/Mesh.h"
#include "graphics/mesh/MaterialBase.h"

#include "utils/FileSystem.h"
#include "utils/Logger.h"

#include <fstream>

Assets& Assets::Instance()
{
	static Assets* instance = new Assets();
	return *instance;
}

void Assets::RegisterAssetsFromFile(const std::string & file)
{
	std::ifstream f("file", std::ios::in);
	std::string line;
	
	while (std::getline(f, line))
	{
		// # considered comment
		if (line[0] == '#') continue;
		if (line.empty()) continue;
	
		// convention is to denote type of file with 'file:path'
		// e.g. texture:"resources/textures"...
		auto pair = FileSystem::Cut(line, ':');
		if (pair.first == "texture")
		{
			LoadTexture(pair.second);
		}
		else if (pair.first == "shader")
		{
			LoadShader(pair.second);
		}
		else if (pair.first == "cubemap")
		{
			LoadCubemap(pair.second);
		}
		else if (pair.first == "mesh")
		{
			LoadMesh(pair.second);
		}
		else if (pair.first == "material")
		{
			LoadMaterial(pair.second);
		}
	}
}

Texture2D* Assets::GetTexture(const std::string & name)
{
	auto it = mTextures.find(name);
	if (it == mTextures.end())
	{
		Logger::Log("Could not find texture with name \"" + name + "\"", WARNING);
		return nullptr;
	}

	return it->second;
}

Shader* Assets::GetShader(const std::string & name)
{
	auto it = mShaders.find(name);
	if (it == mShaders.end())
	{
		Logger::Log("Could not find shader with name \"" + name + "\"", WARNING);
		return nullptr;
	}

	return it->second;
}

Mesh* Assets::GetMesh(const std::string & name)
{
	auto it = mMeshes.find(name);
	if (it == mMeshes.end())
	{
		Logger::Log("Could not find mesh with name \"" + name + "\"", WARNING);
		return nullptr;
	}

	return it->second;
}

MaterialBase* Assets::GetMaterial(const std::string & name)
{
	auto it = mMaterials.find(name);
	if (it == mMaterials.end())
	{
		Logger::Log("Could not find material with name \"" + name + "\"", WARNING);
		return nullptr;
	}

	return it->second;
}

Cubemap* Assets::GetCubemap(const std::string & name)
{
	auto it = mCubemaps.find(name);
	if (it == mCubemaps.end())
	{
		Logger::Log("Could not find cubemap with name \"" + name + "\"", WARNING);
		return nullptr;
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
