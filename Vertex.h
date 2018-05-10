#pragma once
#include "Color.h"

#include <glm\glm.hpp>

struct Vertex {
	glm::vec4 position;
	RGBA32 color;

	Vertex() {}
	Vertex(glm::vec3 pos, RGBA32 c) : position(pos, 1.0f), color(c) {}
};