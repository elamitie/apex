#include "TextureCache.h"
#include "utils/FileSystem.h"

TextureMap TextureCache::mTextureMap;

TextureCache::TextureCache() {
}

TextureCache::~TextureCache() {
}

Texture2D* TextureCache::GetTexture(const std::string& filepath) {
	auto iterator = mTextureMap.find(filepath);

	if (iterator == mTextureMap.end()) {
		Texture2D* tex = new Texture2D();
		tex->Load(FileSystem::GetPath("resources/textures/" + filepath));
		mTextureMap.insert(std::make_pair(filepath, tex));
		return tex;
	}

	return iterator->second;
}