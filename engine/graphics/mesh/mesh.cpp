#include "mesh.h"
#include <sstream>

// DO THE THING

Mesh::Mesh()
{

}

Mesh::Mesh(std::vector<Vertex>& vertices, std::vector<unsigned int>& indices, std::vector<Texture2D*>& textures)
{
	mVertices = vertices;
	mIndices = indices;
	mTextures = textures;

	ConstructMesh();
}

void Mesh::Render(Shader* shader)
{
	GLuint diffuseNr = 1;
	GLuint specularNr = 1;
	for (int i = 0; i < mTextures.size(); i++)
	{
		std::stringstream ss;
		std::string number;
		std::string name = mTextures[i]->mType;
		if (name == "texture_diffuse")
			ss << diffuseNr++;
		else if (name == "texture_specular")
			ss << specularNr++;
		number = ss.str();

		shader->SetUniform(/*"material." + */name + number, i);
		mTextures[i]->Bind(i);
	}
	glActiveTexture(GL_TEXTURE0);

	glBindVertexArray(mVao);
	glDrawElements(GL_TRIANGLES, mIndices.size(), GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}

void Mesh::ConstructMesh()
{
	glGenVertexArrays(1, &mVao);
	glGenBuffers(1, &mVbo);
	glGenBuffers(1, &mIbo);

	glBindVertexArray(mVao);
	glBindBuffer(GL_ARRAY_BUFFER, mVbo);

	glBufferData(GL_ARRAY_BUFFER, mVertices.size() * sizeof(Vertex),
		&mVertices[0], GL_STATIC_DRAW);
	
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mIbo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, mIndices.size() * sizeof(GLuint),
		&mIndices[0], GL_STATIC_DRAW);

	// Vertex Positions
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)0);

	// Vertex Normals
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, Normal));

	// Vertex Textures
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, TexCoords));

	// Vertex Tangents
	// Vertex Bitangents

	glBindVertexArray(0);
}
