#include "sphere.h"
#include "utils/math.h"

const float PI = 3.14159265359f;
const float TAU = 6.28318530717f;

Sphere::Sphere(unsigned int xSeg, unsigned int ySeg)
{
	for (unsigned int y = 0; y <= ySeg; ++y)
	{
		for (unsigned int x = 0; x <= xSeg; ++x)
		{
			float xs = (float)x / (float)ySeg;
			float ys = (float)y / (float)ySeg;

			float xPos = std::cos(xs * TAU) * std::sin(ys * PI);
			float yPos = std::cos(ys * PI);
			float zPos = std::sin(xs * TAU) * std::sin(ys * PI);

			mVertices.push_back(
				{ glm::vec3(xPos, yPos, zPos), glm::vec3(xPos, yPos, zPos), glm::vec2(xs, ys) }
			);
		}
	}

	bool oddRow = false;
	for (int y = 0; y < ySeg; ++y)
	{
		if (!oddRow)
		{
			for (int x = 0; x <= xSeg; ++x)
			{
				mIndices.push_back(y * (xSeg + 1) + x);
				mIndices.push_back((y + 1) * (xSeg + 1) + x);
			}
		}
		else
		{
			for (int x = xSeg; x >= 0; --x)
			{
				mIndices.push_back((y + 1) * (xSeg + 1) + x);
				mIndices.push_back(y       * (xSeg + 1) + x);
			}
		}
		oddRow = !oddRow;
	}

	ConstructMesh();
}