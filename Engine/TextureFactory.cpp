#include "TextureFactory.h"
#include "IOManager.h"
#include "Logger.h"

Texture* TextureFactory::create(std::vector<unsigned char> pixels, int width, int height)
{
	// generate texture
	GLuint id;
	glGenTextures(1, &id);

	// bind texture
	glBindTexture(GL_TEXTURE_2D, id);

	// set texture parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	// set texture content
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, &pixels[0]);

	//unbind texture
	glBindTexture(GL_TEXTURE_2D, 0);
	return new Texture(id, width, height, pixels);
}

Texture * TextureFactory::create(int width, int height, RGBA8 color)
{
	int length = width * height * 4;
	std::vector<unsigned char> pixels = std::vector<unsigned char>(length);

	for (int i = 0; i < length; i+=4) {
		pixels[i] = color.r;
		pixels[i + 1] = color.g;
		pixels[i + 2] = color.b;
		pixels[i + 3] = color.a;
	}

	return create(pixels, width, height);
}

Texture * TextureFactory::createFromFile(std::string filePath)
{
	std::vector<unsigned char> pixels; int w, h;
	pixels = LoadPixelsFromFile(filePath.c_str(), w, h);
return create(pixels, w, h);
}