#pragma once
#include "Primitive.h"

class RaytracerObj
{
public:
	float diffuse;
	float specular;
	Primitive* primitive;

	virtual RGBA32 GetColorAt(glm::vec3 p) { return RGBA32(); }
	virtual glm::vec3 GetNormal(glm::vec3 p) { return glm::vec3(); }
};