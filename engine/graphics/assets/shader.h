#pragma once

// TODO: Abstract the concepts of Attributes and Uniforms into structs of data

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <string>
#include <vector>
#include "utils/types.h"
#include "utils/fileio.h"

typedef std::enable_shared_from_this<Shader> ShaderShared;

class Shader : public ShaderShared {
public:
    Shader() { mProg = glCreateProgram(); }
    ~Shader() { glDeleteProgram(mProg); }

    void Enable();
    void Disable();

    ShaderPtr AddAttribs(const std::vector<std::string>& attribs);
    ShaderPtr Attach(const std::string& filename);
    ShaderPtr Link();

    void SetUniform(const std::string& name, GLint data);
    void SetUniform(const std::string& name, GLint* data, GLsizei count);
    void SetUniform(const std::string& name, GLfloat data);
    void SetUniform(const std::string& name, GLfloat* data, GLsizei count);
    void SetUniform(const std::string& name, const glm::vec2& vector);
    void SetUniform(const std::string& name, const glm::vec3& vector);
    void SetUniform(const std::string& name, const glm::vec4& vector);
    void SetUniform(const std::string& name, const glm::mat4& matrix);

private:
    GLuint Create(const std::string& filename);
    GLint GetUniformLocation(const std::string& uniformName);

private:
    // TODO: support geom shaders
    GLuint mProg, mVert, mFrag;
    int mNumAttribs;

    GLint mStatus, mLength;
};