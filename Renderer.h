#pragma once
#include "Shaderpack.h"
#include "Window.h"

class Renderer
{
public:
	Renderer();
	~Renderer();

	void init();
	void render();

private:
	int _scrWidth;
	int _scrHeight;
	Window _window;
	Shaderpack* _shaderPack;

	void initShaders();
	void initMeshes();
};