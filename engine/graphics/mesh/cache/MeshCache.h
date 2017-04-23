// TODO: Make me more robust

#pragma once

#include "graphics/mesh/Mesh.h"
#include <map>

typedef std::map<std::string, MeshPtr> MeshMap;

class MeshCache {
public:
	static MeshPtr GetMesh(const std::string& filepath);

private:
	MeshCache();
	~MeshCache();

	static MeshMap mMeshMap;
};