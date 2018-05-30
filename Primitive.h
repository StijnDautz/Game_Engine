#pragma once
#include "Ray.h"
#include "Engine\Texture.h"

class Primitive 
{
public:
	virtual bool Intersects(Ray ray, float angle) { return angle < 0; }
	virtual float GetHitLength(Ray ray) { return 0.0f; }
	virtual glm::vec2 GetUv(glm::vec3 p) { return glm::vec2(); }
	virtual glm::vec3 GetNormal(glm::vec3 p) { return glm::vec3(); }
	virtual void DrawDebug(Texture * texture) {}
};