#pragma once
#include "Color.h"

#include <glm\glm.hpp>

struct Vertex {
	glm::vec4 position;
	glm::vec2 uv;

	Vertex() {}
	Vertex(glm::vec3 pos, glm::vec2 UV) : position(pos, 1.0f), uv(UV) {}
};