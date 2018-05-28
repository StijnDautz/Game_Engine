#pragma once
#include "Ray.h"
#include "ColoredObj.h"

class Intersection {
public:
	glm::vec3 p;
	glm::vec3 n;
	Ray ray;
	ColoredObj obj;

	Intersection() {}
	Intersection(Ray r) : ray(r) {}
	~Intersection() {}
};