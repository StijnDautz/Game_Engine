#pragma once
#include <glm/glm.hpp>
#include <GL\glew.h>

//This color type contains 4 floats between the value of 0.0f to 1.0f, it is used for color computations
struct RGBA32 {
	glm::vec4 color;

	RGBA32() : color(glm::vec4(0)) {}
	RGBA32(glm::vec3 c) : color(c, 1.0f) {}
	RGBA32(glm::vec4 c) : color(c) {}
	void set(float R, float G, float B, float A) {
		color.r = R;
		color.g = G;
		color.b = B;
		color.a = A;
	}
	RGBA32* operator+=(RGBA32 i) {
		color += i.color;
		glm::clamp(color, 0.0f, 1.0f);
		return this;
	}
	RGBA32* operator*=(RGBA32 i) {
		color *= i.color;
		return this;
	}
};

//This color type contains 4 bytes between the value of 0 to 255, it is used for rendering
struct RGBA8 {
	GLubyte r, g, b, a;

	RGBA8() : r(0), g(0), b(0), a(0) {}
	void set(RGBA32 c) {
		r = (GLubyte)(c.color.r * 255);
		g = (GLubyte)(c.color.g * 255);
		b = (GLubyte)(c.color.b * 255);
		a = (GLubyte)(c.color.a * 255);
	}
	void set(GLubyte R, GLubyte G, GLubyte B, GLubyte A) {
		r = R;
		g = G;
		b = B;
		a = A;
	}
};