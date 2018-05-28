#pragma once
#include "Engine\Color.h"
#include "Primitive.h"

class ColoredObj
{
public:
	float diffuse;
	float specular;
	RGBA32 color;
	Primitive* primitive;

	ColoredObj() : diffuse(0.0f), specular(0.0f) {}
	ColoredObj(Primitive* p, RGBA32 c) : primitive(p), color(c), diffuse(0.0f), specular(0.0f) {}

	RGBA32 GetColorAt(glm::vec3 p) {
		return color;
	}
};