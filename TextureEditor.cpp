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

// more info on https://en.wikipedia.org/wiki/Bresenham%27s_line_algorithm
void TextureEditor::drawLine(Texture * texture, int x0, int y0, int x1, int y1, RGBA8 color)
{
	int dx = x1 - x0;
	int dy = y1 - y0;
	int d = dy - dx;
	int xInc = -2 * dx;
	int yInc = 2 * dy;

	for (int x = x0; x < x1; x++) {
		drawPixel(texture, x, y0, color);
		if (d > 0) {
			d += -2 * dx;
			y0++;
		}
		d += 2 * dy;
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