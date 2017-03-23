#pragma once

#define GLEW_STATIC
#include <GL/glew.h>
#include <string>

#include "utils/types.h"

enum TextureType {
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

class Texture2D {
    friend class Mesh;
    friend class FrameBuffer;
public:
    Texture2D();
    ~Texture2D();

    void generate(uint width, uint height, ubyte* pixels);

    // This might be changed later if I decide to use an "external"
    // asset loading api
    void load(const std::string& path);
    void bind(unsigned int loc = 0);
    void unbind(unsigned int loc = 0);

private:
    GLuint mId;
    int mWidth, mHeight;
    std::string mPath;
    TextureType mType;

    // GL Data for manual texture construction (framebuffers)
    GLenum mInternalFormat;
    GLenum mImageFormat;
    GLenum mMinFilter;
    GLenum mMaxFilter;
};