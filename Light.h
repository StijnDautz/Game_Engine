#pragma once
#include <glm\glm.hpp>

struct Light {
	glm::vec3 p;
	float intensity;

	Light(glm::vec3 P, float i) : p(P), intensity(i) {}
};