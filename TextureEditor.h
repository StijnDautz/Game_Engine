#pragma once
#include "Texture.h"
#include "Color.h"

class TextureEditor
{
public:
	static void drawPixel(Texture* texture, int x, int y, RGBA8 color);
	static void drawLine(Texture* texture, int x0, int y0, int x1, int y1, RGBA8 color);
	static void drawCircle(Texture* texture, int xc, int yc, int r, RGBA8);
};

