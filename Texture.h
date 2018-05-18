#pragma once
#include "Color.h"

#include <GL\glew.h>
#include <vector>

struct Texture {
	GLuint id;
	int width;
	int height;
	std::vector<unsigned char> pixels;

	Texture(GLuint ID, int w, int h, std::vector<unsigned char> p) : id(ID), width(w), height(h), pixels(p) {}
	~Texture() {}
};