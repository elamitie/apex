#include "Sphere.h"

Sphere::Sphere(int xSegments, int ySegments) {
	const float PI = 3.14159265359;
	for (unsigned int y = 0; y <= ySegments; ++y)
	{
		for (unsigned int x = 0; x <= xSegments; ++x)
		{
			float xSegment = (float)x / (float)xSegments;
			float ySegment = (float)y / (float)ySegments;
			float xPos = std::cos(xSegment * 2.0f * PI) * std::sin(ySegment * PI);
			float yPos = std::cos(ySegment * PI);
			float zPos = std::sin(xSegment * 2.0f * PI) * std::sin(ySegment * PI);

			Vertex vert;
			vert.Position = glm::vec3(xPos, yPos, zPos);
			vert.TexCoords = glm::vec2(xSegment, ySegment);
			vert.Normal = glm::vec3(xPos, yPos, zPos);
			mVertices.push_back(vert);
		}
	}

	bool oddRow = false;
	for (int y = 0; y < ySegments; ++y)
	{
		if (!oddRow) // even rows: y == 0, y == 2; and so on
		{
			for (int x = 0; x <= xSegments; ++x)
			{
				mIndices.push_back(y       * (xSegments + 1) + x);
				mIndices.push_back((y + 1) * (xSegments + 1) + x);
			}
		}
		else
		{
			for (int x = xSegments; x >= 0; --x)
			{
				mIndices.push_back((y + 1) * (xSegments + 1) + x);
				mIndices.push_back(y       * (xSegments + 1) + x);
			}
		}
		oddRow = !oddRow;
	}
	int indexCount = mIndices.size();

	glGenVertexArrays(1, &mVertexArray);
	glBindVertexArray(mVertexArray);

	glGenBuffers(1, &mVertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, mVertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, mVertices.size() * sizeof(Vertex),
		&mVertices.front(), GL_STATIC_DRAW);

	glGenBuffers(1, &mIndexBuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mIndexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, mIndices.size() * sizeof(GLuint),
		&mIndices.front(), GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, Position));
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, Normal));
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, TexCoords));
	glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, Tangents));
	glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, Bitangents));
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);
	glEnableVertexAttribArray(3);
	glEnableVertexAttribArray(4);

	glBindVertexArray(0);
	glDeleteBuffers(1, &mVertexBuffer);
	glDeleteBuffers(1, &mIndexBuffer);
}

void Sphere::Render(Material* mat) {
	glBindVertexArray(mVertexArray);
	glDrawElements(GL_TRIANGLE_STRIP, mIndices.size(), GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}