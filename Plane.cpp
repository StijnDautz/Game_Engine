#include "Plane.h"
#include "Constants.h"

float Plane::GetHitLength(Ray ray)
{
	float denom = dot(n, ray.d);
	if (abs(denom) > 0.0001f)
	{
		float t = dot((p - ray.o), n) / denom;
		if (t >= 0) {
			return t; // you might want to allow an epsilon here too
		}
	}
	return RAYLENGTHCAP;
}

glm::vec2 Plane::GetUv(glm::vec3 _point) 
{
	return glm::vec2(glm::dot(t, _point), glm::dot(b, _point));
}