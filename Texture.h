#pragma once
#include <GL\glew.h>

struct Texture {
	GLuint id;
	int width;
	int height;

	Texture(GLuint ID, int w, int h) : id(ID), width(w), height(h) {}
	~Texture() {}
};