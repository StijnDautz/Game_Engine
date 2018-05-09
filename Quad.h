#pragma once
#include "Vertex.h"

struct Quad {
	Vertex vertexData[6];

	Quad(float x, float y, float w, float h)
	{
		//First Triangle
		vertexData[0].setPosition(x + w, y + h);
		vertexData[1].setPosition(x, y + h);
		vertexData[2].setPosition(x, y);

		//Second Triangle
		vertexData[3].setPosition(x, y);
		vertexData[4].setPosition(x + w, y);
		vertexData[5].setPosition(x + w, y + h);
	}
};