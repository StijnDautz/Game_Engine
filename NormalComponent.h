#pragma once
#include "Primitive.h"
#include "Engine\Texture.h"

#include <glm\glm.hpp>

class NormalComponent {
public:
	virtual glm::vec3 GetNormalAt(glm::vec3 p) { return glm::vec3(); }
};

class PrimitiveNormal : public NormalComponent {
	Primitive* primitive;

public:
	PrimitiveNormal() {}
	PrimitiveNormal(Primitive* p) : primitive(p) {}
	~PrimitiveNormal() {}

	glm::vec3 GetNormalAt(glm::vec3 p) override {
		return primitive->GetNormal(p);
	}
};

class TextureNormal : public NormalComponent {
	Primitive* primitive;
	Texture* normalmap;

public:
	TextureNormal() {}
	TextureNormal(Primitive* p, Texture* t) : primitive(p), normalmap(t) {}
	~TextureNormal() {}

	glm::vec3 GetNormalAt(glm::vec3 p) override {
		glm::vec2 uv = primitive->GetUv(p);
		RGBA32 normals = normalmap->GetColorAt32(uv.x * normalmap->width, uv.y * normalmap->height);
		return glm::normalize(glm::vec3(normals.color.x, normals.color.y, normals.color.z));
	}
};