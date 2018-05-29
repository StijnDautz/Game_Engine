#include "Plane.h"

bool Plane::Intersects(Ray ray)
{
	return (glm::dot(normal, ray.d) > 0); //only if plane's normal makes a 90 degree angle it won't collide
}

float Plane::GetHitLength(Ray ray)
{
	glm::vec3 newPoint = p - ray.o; //point on plane - point on line
	float numeratorDot = glm::dot(newPoint, normal);
	float denominatorDot = glm::dot(ray.d, normal);
	float result = (numeratorDot / denominatorDot);
	if (result < 0) return false;
	return result;
}

glm::vec2 Plane::GetUv(glm::vec3 _point) 
{
	glm::vec3 u = glm::normalize(_point);
	glm::vec3 v = glm::cross(normal, u);
	return glm::vec2(glm::dot(u, _point), glm::dot(v, _point));
}