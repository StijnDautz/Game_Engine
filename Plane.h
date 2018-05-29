#pragma once
#include "Primitive.h";

class Plane : public Primitive
{
public:
	Plane(glm::vec3 _p, glm::vec3 _n) : p(_p), normal(_n) {}
	~Plane();

	bool Intersects(Ray ray) override;
	float GetHitLength(Ray ray) override;
	glm::vec2 GetUv(glm::vec3 p) override;
	glm::vec3 GetNormal(glm::vec3 p) override { return normal; }

private:
	glm::vec3 p;
	glm::vec3 normal;
};
