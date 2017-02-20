#pragma once

#define GLEW_STATIC
#include <GL/glew.h>
#include <string>

class Texture2D
{
public:
	Texture2D();
	~Texture2D();

	// This might be changed later if I decide to use an "external"
	// asset loading api
	void Load(const std::string& path);
	void Bind(unsigned int loc = 0);
	void Unbind(unsigned int loc = 0);

private:
	GLuint m_id;
	int m_width, m_height;
	std::string m_path;
};