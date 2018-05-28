#pragma once
#include "Ray.h"

class Primitive 
{
public:
	virtual bool Intersects(Ray ray) { return false; }
	virtual float GetHitLength(Ray ray) { return 0.0f; }
	virtual glm::vec2 GetUv(glm::vec3 p) { return glm::vec2(); }
	virtual glm::vec3 GetNormal(glm::vec3 p) { return glm::vec3(); }
};