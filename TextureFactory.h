#pragma once
#include "Texture.h"

#include <vector>

class TextureFactory
{
public:
	static Texture* create(std::vector<unsigned char> pixels, int width, int height);
	static Texture* createFromFile(std::string filePath);
};

