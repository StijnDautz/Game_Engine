#pragma once
#include <glm\glm.hpp>

class Ray
{
public:
	glm::vec3 o;
	glm::vec3 d;
	float length;

	static Ray OriginTarget(glm::vec3 origin, glm::vec3 target) {
		Ray r;
		r.o = origin;
		r.SetTarget(target);
		return r;
	}

	static Ray OriginDirection(glm::vec3 origin, glm::vec3 direction) {
		Ray r;
		r.o = origin;
		r.length = glm::length(direction);
		r.d = direction / r.length;
		return r;
	}

	Ray() {}
	Ray(glm::vec3 origin) : o(origin) {}

	glm::vec3 GetTarget() {
		return o + length * d;
	}

	void SetTarget(glm::vec3 target) {
		d = target - o;
		length = glm::length(d);
		d /= length;
	}

	Ray reflection(glm::vec3 origin, glm::vec3 normal) {
		glm::vec3 direction = d - normal * (2.0f * glm::dot(d, normal));
		return Ray::OriginDirection(origin, direction);
	}

	void applyOffset() {
		o = o + 0.00001f * d;
	}
};