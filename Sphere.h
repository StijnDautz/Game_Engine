#pragma once
#include "Primitive.h"

class Sphere : public Primitive
{
public:
	Sphere(glm::vec3 c, float r) : center(c), radius(r), radiusSquared(r * r) {}
	~Sphere() {}

	bool Intersects(Ray ray, float angle) override;
	float GetHitLength(Ray ray) override;
	glm::vec2 GetUv(glm::vec3 p) override;
	glm::vec3 GetNormal(glm::vec3 p) override { return glm::normalize(p - center); }
	void DrawDebug(Texture* texture);

private:
	glm::vec3 center;
	float radius, radiusSquared;
};