// functions in this class have effect ones texture->update is called
#include "TextureEditor.h"

void TextureEditor::drawPixel(Texture * texture, int x, int y, RGBA8 color)
{
	int offset = y * texture->width * 4 + x * 4;
	texture->pixels[offset + 0] = color.r;
	texture->pixels[offset + 1] = color.g;
	texture->pixels[offset + 2] = color.b;
	texture->pixels[offset + 3] = color.a;
}

// code used from https://rosettacode.org/wiki/Bitmap/Bresenham%27s_line_algorithm#C.2B.2B
void TextureEditor::drawLine(Texture* texture, int x1, int y1, int x2, int y2, RGBA8 color)
{
	// Bresenham's line algorithm
	const bool steep = (fabs(y2 - y1) > fabs(x2 - x1));
	if (steep)
	{
		std::swap(x1, y1);
		std::swap(x2, y2);
	}

	if (x1 > x2)
	{
		std::swap(x1, x2);
		std::swap(y1, y2);
	}

	const float dx = x2 - x1;
	const float dy = fabs(y2 - y1);

	float error = dx / 2.0f;
	const int ystep = (y1 < y2) ? 1 : -1;
	int y = (int)y1;

	const int maxX = (int)x2;

	for (int x = (int)x1; x<maxX; x++)
	{
		// check if pixel is within texture boundaries
		if (x < 0 || x > texture->width || y < 0 || y > texture->height) {
			break;
		}
		if (steep) {
			drawPixel(texture, y, x, color);
		}
		else {
			drawPixel(texture, x, y, color);
		}

		error -= dy;
		if (error < 0)
		{
			y += ystep;
			error += dx;
		}
	}
}


// code used from https://en.wikipedia.org/wiki/Midpoint_circle_algorithm
void TextureEditor::drawCircle(Texture * texture, int x0, int y0, int r, RGBA8 color)
{
	int x = r - 1;
	int y = 0;
	int dx = 1;
	int dy = 1;
	int err = dx - (r << 1);

	while (x >= y) {
		drawPixel(texture, x0 + x, y0 + y, color);
		drawPixel(texture, x0 + y, y0 + x, color);
		drawPixel(texture, x0 - y, y0 + x, color);
		drawPixel(texture, x0 - x, y0 + y, color);
		drawPixel(texture, x0 - x, y0 - y, color);
		drawPixel(texture, x0 - y, y0 - x, color);
		drawPixel(texture, x0 + y, y0 - x, color);
		drawPixel(texture, x0 + x, y0 - y, color);

		if (err <= 0) {
			y++;
			err += dy;
			dy += 2;
		}

		if (err > 0) {
			x--;
			dx += 2;
			err += dx - (r << 1);
		}
	}
}