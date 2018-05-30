#pragma once
#include <glm/glm.hpp>
#include <GL\glew.h>

//This color type contains 4 bytes between the value of 0 to 255, it is used for rendering
struct RGBA8 {
	GLubyte r, g, b, a;

	RGBA8() : r(0), g(0), b(0), a(0) {}
	RGBA8(GLubyte R, GLubyte G, GLubyte B, GLubyte A) : r(R), g(G), b(B), a(A) {}

	void set(GLubyte R, GLubyte G, GLubyte B, GLubyte A) {
		r = R;
		g = G;
		b = B;
		a = A;
	}
};

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
	void clamp() {
		color = glm::clamp(color, glm::vec4(), glm::vec4(1.0f));
	}

	RGBA8 toRGBA8() {
		color *= 255.0f;
		return RGBA8((GLubyte)color.r, (GLubyte)color.g, (GLubyte)color.b, (GLubyte)color.a);
	}

	void operator+=(RGBA32 i) {
		color += i.color;
		//glm::clamp(color, 0.0f, 1.0f);
	}
	RGBA32* operator*=(RGBA32 i) {
		color *= i.color;
		return this;
	}
	RGBA32 operator*(RGBA32 i) {
		color *= i.color;
		return *this;
	}
	void operator*=(float f) {
		color *= f;
	}
	RGBA32 operator*(float f) {
		color *= f;
		return *this;
	}
	RGBA32 operator/(float f) {
		color /= f;
		return *this;
	}
};