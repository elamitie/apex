#pragma once

#include "graphics/mesh/Mesh.h"

class Sphere : public Mesh {
public:
	Sphere(int xSegments, int ySegments);

	void Render(MaterialBase* mat) override;
};