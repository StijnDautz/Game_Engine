#pragma once
#include <glm\glm.hpp>

struct Light {
	glm::vec3 p;
	glm::vec3 intensity;

	Light(glm::vec3 P, glm::vec3 i) : p(P), intensity(i) {}
};