#pragma once
#include <string>
#include <SDL/SDL.h>

class Window
{
public:
	Window();
	Window(std::string name, int w, int h);
	~Window();

	void setDimensions(float w, float h);
	void SetBackgroundColor(float r, float g, float b);
	void swap();

private:
	int _width;
	int _height;
	SDL_Window* _sdlWindow;
};