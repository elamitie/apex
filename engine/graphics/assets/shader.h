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

    void AddAttribute(const std::string& name);

    void Bind();
    void Unbind();

    void SetUniform(const std::string& name, GLint data);
    void SetUniform(const std::string& name, GLint* data, GLsizei count);
    void SetUniform(const std::string& name, GLfloat data);
    void SetUniform(const std::string& name, GLfloat* data, GLsizei count);
    void SetUniform(const std::string& name, const glm::vec2& vector);
    void SetUniform(const std::string& name, const glm::vec3& vector);
    void SetUniform(const std::string& name, const glm::vec4& vector);
    void SetUniform(const std::string& name, const glm::mat4& matrix);

private:
    GLint GetUniformLocation(const std::string& uniformName);
    void Compile(const std::string& shader, GLuint shaderID);
    void Link();

private:
    // TODO: support geom shaders
    GLuint mProg, mVert, mFrag;
    int mNumAttribs;
};