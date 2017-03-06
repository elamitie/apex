#pragma once

#define GLEW_STATIC
#include <GL/glew.h>
#include <string>

enum TextureType
{
	DIFFUSE,
	SPECULAR,
	NORMAL,
	HEIGHTMAP,
	NUM_TYPES
};
static const char* TextureTypeStr[] = {
	"diffuse",
	"specular",
	"normal",
	"heightmap"
};

class Texture2D
{
	friend class Mesh;
public:
	Texture2D();
	~Texture2D();

	// This might be changed later if I decide to use an "external"
	// asset loading api
	void Load(const std::string& path);
	void Bind(unsigned int loc = 0);
	void Unbind(unsigned int loc = 0);

private:
	GLuint mId;
	int mWidth, mHeight;
	std::string mPath;
	TextureType mType;
};