#pragma once
#include "RaytracerObj.h"

class NormalMapObj : public RaytracerObj
{
public:
	RGBA32 color;
	Texture* normalMap;

	NormalMapObj() : color(RGBA32()), normalMap(nullptr) {
		primitive = nullptr;
		diffuse = 0.0f;
		specular = 0.0f;
	}
	NormalMapObj(Primitive* p, RGBA32 c, Texture* n) : color(c), normalMap(n) {
		primitive = p;
		diffuse = 0.0f;
		specular = 0.0f;
	}

	RGBA32 GetColorAt(glm::vec3 p) override {
		return color;
	}

	glm::vec3 GetNormal(glm::vec3 p) override {
		glm::vec2 uv = primitive->GetUv(p);
		RGBA32 normals = normalMap->GetColorAt32(uv.x * normalMap->width, uv.y * normalMap->height);
		return glm::normalize(glm::vec3(normals.color.x, normals.color.y, normals.color.z));
	}
};