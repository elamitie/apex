#pragma once

#include <GL/glew.h>
#include <vector>

#include "../../utils/rendering_types.h"
#include "../assets/shader.h"
#include "../assets/texture.h"
#include "vertex.h"

// Ethan's Note: Eventually will support model loading w/ assimp.
// Models would extend (or own) this class. Primitives will inherit
// from this class.

class Mesh
{
public:
	Mesh(std::vector<Vertex>& vertices, std::vector<unsigned int>& indices, std::vector<TexturePtr>& textures);

	inline std::vector<TexturePtr> GetTextures() { return mTextures; }
	inline std::vector<Vertex> GetVertices() { return mVertices; }
	inline std::vector<unsigned int> GetIndices() { return mIndices; }

	// Later this should definitely be part of a renderer, not here.
	void Draw(ShaderPtr shader);

private:
	void ConstructMesh();

private:
	std::vector<TexturePtr> mTextures;
	std::vector<Vertex> mVertices;
	std::vector<unsigned int> mIndices;

	GLuint mVao, mVbo, mIbo;
};