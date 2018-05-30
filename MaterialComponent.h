#pragma once
#include "Primitive.h"

#include "Engine\Color.h"
#include "Engine\Texture.h"

class MaterialComponent {
public:
	virtual RGBA32 GetColorAt(glm::vec3 p) { return RGBA32(); }
};

class ColorMaterial : public MaterialComponent {
	RGBA32 color;

public:
	ColorMaterial() {}
	ColorMaterial(RGBA32 c) : color(c) {}
	~ColorMaterial() {}

	RGBA32 GetColorAt(glm::vec3 p) override { return color; }
};

class TextureMaterial : public MaterialComponent {
	Primitive* primitive;
	Texture* texture;

public:
	TextureMaterial() {}
	TextureMaterial(Primitive* p, Texture* t) : primitive(p), texture(t) {}
	~TextureMaterial() {}

	RGBA32 GetColorAt(glm::vec3 p) override {
		glm::vec2 uv = primitive->GetUv(p);
		return texture->GetColorAt32(uv.x * texture->width, uv.y * texture->height);
	}
};