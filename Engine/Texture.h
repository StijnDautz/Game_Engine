#pragma once
#include "Color.h"

#include <GL\glew.h>
#include <vector>

struct Texture {
	GLuint id;
	int width;
	int height;
	std::vector<unsigned char> pixels;

	Texture(GLuint ID,int w, int h, std::vector<unsigned char> p) : id(ID), width(w), height(h), pixels(p) {}
	~Texture() {}

	void update()
	{
		glBindTexture(GL_TEXTURE_2D, id);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, &pixels[0]);
		glBindTexture(GL_TEXTURE_2D, 0);
	}
};