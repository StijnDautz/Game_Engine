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
		//return (int)(p.x + p.y - p.z - 1) % 2 ? RGBA32(glm::vec3(0.6f, 0.5f, 0.1f)) : RGBA32(glm::vec3(0.8f, 0.8f, 0.8f));
	}
};