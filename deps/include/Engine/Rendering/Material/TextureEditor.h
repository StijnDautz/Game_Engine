#pragma once
#include "Texture.h"
#include "Color.h"

class TextureEditor
{
public:
	static void drawPixel(Texture* texture, int x, int y, RGBA8 color);
	static void drawLine(Texture * texture, int x1, int y1, int x2, int y2, RGBA8 color);
	static void drawCircle(Texture* texture, int xc, int yc, int r, RGBA8);
};

