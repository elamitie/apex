// TODO: Make me more robust

#pragma once

#include "graphics/assets/Texture.h"
#include <map>

typedef std::map<std::string, Texture2D*> TextureMap;

class TextureCache {
public:
	static Texture2D* GetTexture(const std::string& filepath);

private:
	TextureCache();
	~TextureCache();

	static TextureMap mTextureMap;
};