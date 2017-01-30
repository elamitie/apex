#include "shader.h"
#include <fstream>
#include <vector>
#include <iostream>

Shader::Shader(const std::string& vert, const std::string& frag)
{
	mProg = glCreateProgram();
	mVert = glCreateShader(GL_VERTEX_SHADER);
	mFrag = glCreateShader(GL_FRAGMENT_SHADER);

	Compile(vert, mVert);
	Compile(frag, mFrag);

	Link();
}

Shader::~Shader()
{

}

void Shader::AddAttribute(const std::string& name)
{
	glBindAttribLocation(mProg, mNumAttribs++, name.c_str());
}

void Shader::Bind()
{
	glUseProgram(mProg);
	for (int i = 0; i < mNumAttribs; i++)
	{
		glEnableVertexAttribArray(i);
	}
}

void Shader::Unbind()
{
	glUseProgram(0);
	for (int i = 0; i < mNumAttribs; i++)
	{
		glDisableVertexAttribArray(i);
	}
}

GLint Shader::GetUniformLocation(const std::string& uniformName)
{
	GLint location = glGetUniformLocation(mProg, uniformName.c_str());
	if (location == GL_INVALID_INDEX)
		std::cout << "could not find uniform name" << std::endl;
	return location;
}

void Shader::Compile(const std::string& shader, GLuint shaderID)
{
	std::ifstream file(shader);
	std::string filecontents = "";
	std::string line;

	while (std::getline(file, line))
		filecontents += line + "\n";

	file.close();

	const char* contents = filecontents.c_str();
	glShaderSource(shaderID, 1, &contents, nullptr);
	glCompileShader(shaderID);

	GLint success = 0;
	glGetShaderiv(shaderID, GL_COMPILE_STATUS, &success);

	if (success == GL_FALSE)
	{
		GLint maxLength = 0;
		glGetShaderiv(shaderID, GL_INFO_LOG_LENGTH, &maxLength);

		std::vector<char> errorLog(maxLength);
		glGetShaderInfoLog(shaderID, maxLength, &maxLength, &errorLog[0]);

		std::printf("%s\n", &errorLog[0]);

		glDeleteShader(shaderID);
		return;
	}
}

void Shader::Link()
{
	glAttachShader(mProg, mVert);
	glAttachShader(mProg, mFrag);

	glLinkProgram(mProg);

	GLint isLinked = 0;
	glGetProgramiv(mProg, GL_LINK_STATUS, (int*)&isLinked);
	if (isLinked == GL_FALSE)
	{
		GLint maxLength = 0;
		glGetProgramiv(mProg, GL_INFO_LOG_LENGTH, &maxLength);

		std::vector<char> errorLog(maxLength);
		glGetProgramInfoLog(mProg, maxLength, &maxLength, &errorLog[0]);

		glDeleteProgram(mProg);
		glDeleteShader(mVert);
		glDeleteShader(mFrag);

		std::printf("%s\n", &errorLog[0]);
		return;
	}

	glDetachShader(mProg, mVert);
	glDetachShader(mProg, mFrag);
	glDeleteShader(mVert);
	glDeleteShader(mFrag);
}

void Shader::SetUniform(const std::string& name, GLint data)
{
	GLint location = GetUniformLocation(name);
	glUniform1i(location, data);
}

void Shader::SetUniform(const std::string& name, GLint* data, GLsizei count)
{
	GLint location = GetUniformLocation(name);
	glUniform1iv(location, count, data);
}

void Shader::SetUniform(const std::string& name, GLfloat data)
{
	GLint location = GetUniformLocation(name);
	glUniform1f(location, data);
}

void Shader::SetUniform(const std::string& name, GLfloat* data, GLsizei count)
{
	GLint location = GetUniformLocation(name);
	glUniform1fv(location, count, data);
}

void Shader::SetUniform(const std::string& name, const glm::vec2& vector)
{
	GLint location = GetUniformLocation(name);
	glUniform2f(location, vector.x, vector.y);
}

void Shader::SetUniform(const std::string& name, const glm::vec3& vector)
{
	GLint location = GetUniformLocation(name);
	glUniform3f(location, vector.x, vector.y, vector.z);
}

void Shader::SetUniform(const std::string& name, const glm::vec4& vector)
{
	GLint location = GetUniformLocation(name);
	glUniform4f(location, vector.x, vector.y, vector.z, vector.w);
}

void Shader::SetUniform(const std::string& name, const glm::mat4& matrix)
{
	GLint location = GetUniformLocation(name);
	glUniformMatrix4fv(location, 1, GL_FALSE, &(matrix[0][0]));
}