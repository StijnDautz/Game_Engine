#pragma once
#include "Color.h"

#include <glm\glm.hpp>

struct Vertex {
	glm::vec3 position;
	glm::vec2 uv;
	RGBA8 color;
};