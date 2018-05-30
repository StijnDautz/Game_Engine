#include "Triangle.h"

bool Triangle::Intersects(Ray ray, float angle)
{
	//Parallel:
	if (glm::dot(normal, ray.o) == 0) return false;
	glm::vec3 edge0 = v1 - v0;
	glm::vec3 edge1 = v2 - v1;
	glm::vec3 edge2 = v0 - v2;
	glm::vec3 intersectPoint = ray.o + GetHitLength(ray) * ray.d;
	glm::vec3 var0 = intersectPoint - v0;
	glm::vec3 var1 = intersectPoint - v1;
	glm::vec3 var2 = intersectPoint - v2;

	if (glm::dot(normal, glm::cross(edge0, var0)) < 0 ||
		glm::dot(normal, glm::cross(edge1, var1)) < 0 ||
		glm::dot(normal, glm::cross(edge2, var2)) < 0) return false;
	return true;
}

float Triangle::GetHitLength(Ray ray)
{
	glm::vec3 newPoint = v0 - ray.o; //point on plane - point on line
	float numeratorDot = glm::dot(newPoint, normal);
	float denominatorDot = glm::dot(ray.d, normal);
	float result = numeratorDot / denominatorDot;
	if (result < 0) return false;
	return result;
}

glm::vec3 Triangle::GetNormal(glm::vec3 _v0, glm::vec3 _v1, glm::vec3 _v2)
{
	glm::vec3 temp1 = _v0 - _v1;
	glm::vec3 temp2 = _v1 - _v2;
	glm::vec3 result = glm::cross(temp2, temp1);

	return (glm::normalize(result));
}

glm::vec2 Triangle::GetUv(glm::vec3 _point) {
	glm::vec3 u = glm::normalize(_point);
	glm::vec3 v = glm::cross(normal, u);
	return glm::vec2(glm::dot(u, _point), glm::dot(v, _point));
}