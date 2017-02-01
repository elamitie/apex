#pragma once

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <vector>

// Ethan's Note: Eventually will support model loading w/ assimp.
// Models would extend (or own) this class. Primitives will inherit
// from this class.

// TODO: Abstract concept of a vertex would avoid testy stuff like this
typedef std::vector<glm::vec2> Vec2Array;
typedef std::vector<glm::vec3> Vec3Array;
typedef std::vector<unsigned int> UIntArray;

enum MeshTopology
{
	POINTS,
	LINES,
	LINE_STRIP,
	TRIANGLES,
	TRIANGLE_STRIP,
	TRIANGLE_FAN
};

class Mesh
{
public:
	Mesh(Vec3Array& positions, UIntArray& indices);
	Mesh(Vec3Array& positions, Vec2Array& uv, UIntArray& indices);
	Mesh(Vec3Array& positions, Vec2Array& uv, Vec3Array& normals, UIntArray& indices);
	Mesh(Vec3Array& positions, Vec2Array& uv, Vec3Array& normals, Vec3Array& tangents, Vec3Array& bitangents, UIntArray& indices);
	
public:
private:
};