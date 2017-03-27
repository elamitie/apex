#include "MeshCache.h"

MeshMap MeshCache::mMeshMap;

MeshCache::MeshCache() {
}

MeshCache::~MeshCache() {
}

MeshPtr MeshCache::GetMesh(const std::string& filepath) {
	auto iterator = mMeshMap.find(filepath);

	if (iterator == mMeshMap.end()) {
		MeshPtr mesh = std::make_shared<Mesh>(filepath);
		mMeshMap.insert(std::make_pair(filepath, mesh));
		return mesh;
	}

	return iterator->second;
}