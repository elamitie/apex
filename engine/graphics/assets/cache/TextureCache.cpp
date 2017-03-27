#include "TextureCache.h"

TextureMap TextureCache::mTextureMap;

TextureCache::TextureCache() {
}

TextureCache::~TextureCache() {
}

TexturePtr TextureCache::GetTexture(const std::string& filepath) {
	auto iterator = mTextureMap.find(filepath);

	if (iterator == mTextureMap.end()) {
		TexturePtr tex = std::make_shared<Texture2D>();
		tex->Load(filepath);
		mTextureMap.insert(std::make_pair(filepath, tex));
		return tex;
	}

	return iterator->second;
}