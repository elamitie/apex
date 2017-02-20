#include "mesh.h"

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

void Mesh::Draw(Shader* shader)
{
	// This method will probably change, a lot.
	// For now, because we aren't handling ASSIMP yet, I'm going to assume
	// there is only ever one texture.
	shader->SetUniform("ourTexture", 0);
	mTextures[0]->Bind();

	glBindVertexArray(mVao);
	if (mIndices.size() > 0)
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
