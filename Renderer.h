#pragma once
#include "Shaderpack.h"
#include "Sprite.h"

#include <SDL\SDL.h>

class Renderer
{
public:
	Renderer();
	Renderer(int width, int height);
	~Renderer();

	void init();
	void render();

private:
	int _scrWidth;
	int _scrHeight;
	SDL_Window* _window;
	Shaderpack _shaderPack;
	Sprite* _sprite;

	void initOpenGL();
	void initShaders();
};