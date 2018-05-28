#include "Sphere.h"

bool Sphere::Intersects(Ray ray)
{
	glm::vec3 toCenter = center - ray.o;
	float toCenterSquared = glm::dot(toCenter, toCenter);
	float projection = glm::dot(ray.d, toCenter);
	if (projection < 0) {
		return false;
	}
	float projectionSquared = glm::dot(projection, projection);
	return toCenterSquared - projectionSquared <= radiusSquared;
}

float Sphere::GetHitLength(Ray ray)
{
	glm::vec3 toCenter = center - ray.o;
	float toCenterSquared = glm::dot(toCenter, toCenter);
	float projection = glm::dot(ray.d, toCenter);
	if (projection < 0) {
		return false;
	}
	float projectionSquared = glm::dot(projection, projection);
	float D = toCenterSquared - projectionSquared;
	if (D > radiusSquared) {
		return 1000000000.0f;
	}

	return projection - glm::sqrt(radiusSquared - D);
}
