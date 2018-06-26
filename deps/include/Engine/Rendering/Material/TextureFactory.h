#pragma once
#include "Texture.h"

#include <vector>

class TextureFactory
{
public:
	static Texture* create(std::vector<unsigned char> pixels, int width, int height);
	static Texture* create(int width, int height, RGBA8 color);
	static Texture* loadFromFile(std::string filePath);
};

