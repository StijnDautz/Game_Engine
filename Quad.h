#pragma once
#include "Vertex.h"

struct Quad {
	Vertex vertexData[6];

	Quad(float x, float y, float w, float h)
	{
		//First Triangle
		vertexData[0].position = glm::vec3(x + w, y + h, 0);
		vertexData[1].position = glm::vec3(x, y + h, 0);
		vertexData[2].position = glm::vec3(x, y, 0);

		//Second Triangle
		vertexData[3].position = glm::vec3(x, y, 0);
		vertexData[4].position = glm::vec3(x + w, y, 0);
		vertexData[5].position = glm::vec3(x + w, y + h, 0);
	}
};