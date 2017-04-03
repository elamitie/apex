#pragma once

#include <GL/glew.h>
#include <vector>

class Cubemap {
public:
    Cubemap();
    ~Cubemap();

	void Create(int width, int height, bool mipmaps = false);

    void Load(const std::vector<std::string>& faces);
    void Bind(unsigned int loc = 0);
    void Unbind(unsigned int loc = 0);

	inline unsigned int GetHandle() { return mId; }

public:
	// Mostly just used for generating PBR cubemaps
	GLenum minFilter = GL_LINEAR;
	GLenum magFilter = GL_LINEAR;

private:
    GLuint mId;

    // Collection of texture paths to load
    std::vector<std::string> mFacePaths;
};