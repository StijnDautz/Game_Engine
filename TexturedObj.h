#pragma once
#include "RaytracerObj.h"

class TexturedObj : public RaytracerObj 
{
public:
	Texture* texture;

	TexturedObj() {
		diffuse = 0.0f;
		specular = 0.0f;
		texture = nullptr;
	}
	TexturedObj(Primitive* p, Texture* t) : texture(t) {
		diffuse = 0.0f;
		specular = 0.0f;
		primitive = p;
	}
	TexturedObj(Primitive* p, Texture* t, float d, float s) : texture(t){
		primitive = p;
		diffuse = d;
		specular = s;
	}

	RGBA32 GetColorAt(glm::vec3 p) override {
		glm::vec2 uv = primitive->GetUv(p);
		return texture->GetColorAt32(uv.x * texture->width, uv.y * texture->height);
	}

	glm::vec3 GetNormal(glm::vec3 p) override {
		return primitive->GetNormal(p);
	}
}; 