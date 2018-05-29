#pragma once
#include "Engine\Color.h"
#include "RaytracerObj.h"

class ColoredObj : public RaytracerObj
{
public:
	RGBA32 color;

	ColoredObj() {
		diffuse = 0.0f;
		specular = 0.0f;
	}
	// used for mirror objects, as they do not need a color
	ColoredObj(Primitive* p) {
		primitive = p;
		diffuse = 0.0f;
		specular = 1.0f;
	}
	ColoredObj(Primitive* p, RGBA32 c) : color(c) {
		primitive = p;
		diffuse = 0.0f;
		specular = 0.0f;
	}
	ColoredObj(Primitive* p, RGBA32 c, float d, float s) : color(c) {
		primitive = p;
		diffuse = d;
		specular = s;
	}

	RGBA32 GetColorAt(glm::vec3 p) {
		return color;
	}

	glm::vec3 GetNormal(glm::vec3 p) override {
		return primitive->GetNormal(p);
	}
};