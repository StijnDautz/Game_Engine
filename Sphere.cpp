#include "Sphere.h"
#include "Constants.h"
#include "Engine\TextureEditor.h"

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

float Sphere::GetHitLength(Ray ray) {
	glm::vec3 toCenter = center - ray.o;
	float toCenterSquared = glm::dot(toCenter, toCenter);
	float projection = glm::dot(ray.d, toCenter);

	// if ray is going in the oppositve direction, they will never hit
	if (projection < 0) {
		return RAYLENGTHCAP;
	}
	float projectionSquared = glm::dot(projection, projection);
	float D = toCenterSquared - projectionSquared;

	// if ray does not hit the sphere
	if (D > radiusSquared) {
		return RAYLENGTHCAP;
	}

	return projection - glm::sqrt(radiusSquared - D);
}

glm::vec2 Sphere::GetUv(glm::vec3 p)
{
	glm::vec3 n = p - center;
	float length = glm::length(n);
	float u = 0.5f + std::atan2(n.z, n.x) / PI2;
	float v = 0.5f - std::asin(n.y) / PI;
	return glm::vec2(u, v);
}

void Sphere::DrawDebug(Texture * texture)
{
	glm::vec3 textureCoords = glm::vec3(center.x, 0, center.z);
	texture->worldToTextureCoords(20, 0, 0, textureCoords);
	TextureEditor::drawCircle(texture, textureCoords.x, textureCoords.z, radius * (512 / 20), RGBA8(120, 230, 255, 255));
}

/*
glm::vec3 centerToOrigin = ray.o - center;
float a = 1.0f; // a < 1 how...?
float b = 2.0f * glm::dot(ray.d, centerToOrigin);
float c = glm::dot(centerToOrigin, centerToOrigin) - radiusSquared;

float d = b * b - 4 * a * c;
if (d < 0.0f) {
return RAYLENGTHCAP;
}
else
{
float sqrtD = glm::sqrt(d);
float t0 = (-b + sqrtD) / (2 * a);
float t1 = (-b - sqrtD) / (2 * a);
return t0 < t1 ? t0 : t1;
}*/