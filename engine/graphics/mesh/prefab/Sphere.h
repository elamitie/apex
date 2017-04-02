#pragma once

#include "graphics/mesh/Mesh.h"

class Sphere : public Mesh {
public:
	Sphere(int xSegments, int ySegments);

	void Render(Material* mat) override;
};