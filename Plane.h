#pragma once
#include "Primitive.h"
#include "Engine\Logger.h"

class Plane : public Primitive
{
public:
	Plane(glm::vec3 point, glm::vec3 normal, glm::vec3 tangent) : p(point), n(normal), t(tangent) {
		float l = glm::length(p);
		if (p.x == 0 || p.y == l || p.z == l) {
			fatalError("point on plane cannot have 2x an 0.0f attribute");
		}
		b = glm::cross(t, n);
	}
	~Plane() {}

	float GetHitLength(Ray ray) override;
	glm::vec2 GetUv(glm::vec3 p) override;
	glm::vec3 GetNormal(glm::vec3 p) override { return n; }

private:
	glm::vec3 p;	// point
	glm::vec3 n;	// normal
	glm::vec3 t;	// tangent
	glm::vec3 b;	// bitangent
};
