#pragma once
#include "Color.h"

#include <GL\glew.h>
#include <vector>
#include "Color.h"

struct UV {
	int u;
	int v;

	UV(int U, int V) : u(U), v(V) {}
};

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

	UV worldToTextureCoords(int size, int cx, int cy, glm::vec3 v) {
		// convert world to screen coords using a 10x10 box
		float boundary = size * 0.5f;
		return UV((int)(boundary + v.x + cx) * (width / size), (int)(boundary - v.z + cy) * (height / size));
	}

	void clear() {
		for (unsigned int i = 0; i < pixels.size(); i++) {
			pixels[i] = 0;
		}
	}

	RGBA8 GetColorAt8(int x, int y) {
		int offset = y * width + x;
		return RGBA8(pixels[offset], pixels[offset + 1], pixels[offset + 2], pixels[offset + 3]);
	}
	RGBA32 GetColorAt32(int x, int y) {
		int offset = (y * width * 4 + x * 4) % pixels.size();
		float i = 1 / 255.0f;
		return RGBA32(glm::vec3(pixels[offset] * i, pixels[offset + 1] * i, pixels[offset + 2] * i));
	}
};