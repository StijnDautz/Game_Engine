#pragma once
#include "Color.h"

#include <glm\glm.hpp>

struct Vertex {
	glm::vec3 position;
	glm::vec2 uv;
	glm::vec3 normal;

	Vertex() {}
	Vertex(glm::vec3 pos, glm::vec2 UV, glm::vec3 n) : position(pos), uv(UV), normal(n) {}
};