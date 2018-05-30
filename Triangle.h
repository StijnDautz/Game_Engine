#pragma once
#include "Primitive.h"

class Triangle : public Primitive
{
public:
	Triangle(glm::vec3 _v0, glm::vec3 _v1, glm::vec3 _v2) : v0(_v0), v1(_v1), v2(_v2) {}
	~Triangle() {}

	bool Intersects(Ray ray, float angle) override;
	float GetHitLength(Ray ray) override;
	glm::vec2 GetUv(glm::vec3 p) override;
	glm::vec3 GetNormal(glm::vec3 p) override { return normal; }

private:
	glm::vec3 v0, v1, v2;
	glm::vec3 GetNormal(glm::vec3 _v0, glm::vec3 _v1, glm::vec3 _v2);
	glm::vec3 normal = GetNormal(v0, v1, v2);
};
