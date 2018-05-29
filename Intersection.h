#pragma once
#include "Ray.h"
#include "RaytracerObj.h"

class Intersection {
public:
	glm::vec3 p;
	glm::vec3 n;
	Ray ray;
	RaytracerObj* obj;

	Intersection() {}
	Intersection(Ray r) : ray(r) {}
	~Intersection() {}
};