#include "texture.h"
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>


Texture2D::Texture2D()
{

}

Texture2D::~Texture2D()
{

}

void Texture2D::Load(const std::string& path)
{
	glGenTextures(1, &m_id);
	glBindTexture(GL_TEXTURE_2D, m_id);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);

	stbi_set_flip_vertically_on_load(true);

	int _width, _height, _nrComponents;
	unsigned char* data = stbi_load(path.c_str(), &_width, &_height, &_nrComponents, 0);
	if (data)
	{
		GLenum format;
		if (_nrComponents == 1)
			format = GL_RED;
		if (_nrComponents == 3)
			format = GL_RGB;
		if (_nrComponents == 4)
			format = GL_RGBA;

		glTexImage2D(GL_TEXTURE_2D, 0, format, _width, _height, 0, format, GL_UNSIGNED_BYTE, data);

		glGenerateMipmap(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, 0);

		stbi_image_free(data);
	}
}

void Texture2D::Bind(unsigned int loc /*= 0*/)
{
	if (loc >= 0)
		glActiveTexture(GL_TEXTURE0 + loc);
	glBindTexture(GL_TEXTURE_2D, m_id);
}

void Texture2D::Unbind(unsigned int loc /*= 0*/)
{
	glBindTexture(GL_TEXTURE_2D, 0);
}
