// TODO: Make me more robust

#pragma once

#include "graphics/assets/Texture.h"
#include <map>

typedef std::map<std::string, TexturePtr> TextureMap;

class TextureCache {
public:
	static TexturePtr GetTexture(const std::string& filepath);

private:
	TextureCache();
	~TextureCache();

	static TextureMap mTextureMap;
};