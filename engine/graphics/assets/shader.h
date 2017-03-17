#pragma once

// TODO: Abstract the concepts of Attributes and Uniforms into structs of data

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <string>

class Shader
{
public:
    Shader(const std::string& vertPath, const std::string& fragPath);
    ~Shader();

    void addAttribute(const std::string& name);

    void enable();
    void disable();

    void setUniform(const std::string& name, GLint data);
    void setUniform(const std::string& name, GLint* data, GLsizei count);
    void setUniform(const std::string& name, GLfloat data);
    void setUniform(const std::string& name, GLfloat* data, GLsizei count);
    void setUniform(const std::string& name, const glm::vec2& vector);
    void setUniform(const std::string& name, const glm::vec3& vector);
    void setUniform(const std::string& name, const glm::vec4& vector);
    void setUniform(const std::string& name, const glm::mat4& matrix);

private:
    GLint getUniformLocation(const std::string& uniformName);
    void compile(const std::string& shader, GLuint shaderID);
    void link();

private:
    // TODO: support geom shaders
    GLuint mProg, mVert, mFrag;
    int mNumAttribs;
};