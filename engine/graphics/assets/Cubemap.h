#pragma once

#include <GL/glew.h>
#include <vector>

class Cubemap {
public:
    Cubemap();
    ~Cubemap();

    void Load(const std::vector<std::string>& faces);
    void Bind(unsigned int loc = 0);
    void Unbind(unsigned int loc = 0);

private:
    GLuint mId;

    // Collection of texture paths to load
    std::vector<std::string> mFacePaths;
};