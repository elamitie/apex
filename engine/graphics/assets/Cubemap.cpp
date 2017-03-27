#include "Cubemap.h"
#include <stb_image.h>

#include "utils/FileSystem.h"
#include "utils/Logger.h"

Cubemap::Cubemap() {
    glGenTextures(1, &mId);
}

Cubemap::~Cubemap() {
    glDeleteTextures(1, &mId);
}

void Cubemap::Load(const std::vector<std::string>& faces) {
    glActiveTexture(GL_TEXTURE0);
    int width, height, nrComponents;
    unsigned char* pixels;

    glBindTexture(GL_TEXTURE_CUBE_MAP, mId);
    for (int i = 0; i < faces.size(); i++) {
        std::string path = FileSystem::GetPath("resources/textures/skybox_lake/" + faces[i]);
        pixels = stbi_load(path.c_str(), &width, &height, &nrComponents, 0);
        GLenum format;
        if (nrComponents == 1)
            format = GL_RED;
        if (nrComponents == 3)
            format = GL_RGB;
        if (nrComponents == 4)
            format = GL_RGBA;

        glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB,
                     width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, pixels);
    }

    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
    glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
}

void Cubemap::Bind(unsigned int loc /*= 0*/) {
    if (loc >= 0)
        glActiveTexture(GL_TEXTURE0 + loc);
    glBindTexture(GL_TEXTURE_CUBE_MAP, mId);
}

void Cubemap::Unbind(unsigned int loc /*= 0*/) {
    glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
}