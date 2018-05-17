#include "TextureFactory.h"
#include "IOManager.h"
#include "Logger.h"

Texture* TextureFactory::create(std::vector<unsigned char> pixels, int width, int height)
{
	// texture handle
	GLuint texture;

	// generate texture
	glGenTextures(1, &texture);

	// bind the texture
	glBindTexture(GL_TEXTURE_2D, texture);

	// set texture parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	// set texture content
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, &pixels[0]);
	return new Texture(texture, width, height);
}

Texture * TextureFactory::createFromFile(std::string filePath)
{
	std::vector<unsigned char> pixels; int w, h;
	pixels = LoadPixelsFromFile(filePath.c_str(), w, h);
	return create(pixels, w, h);
}