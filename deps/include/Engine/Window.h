#pragma once
#include <string>
#include <SDL/SDL.h>

class Window
{
public:
	Window();
	Window(std::string name, int w, int h);
	~Window();

	int width;
	int height;

	void setDimensions(int w, int h);
	void SetBackgroundColor(float r, float g, float b);
	void swap();

private:
	SDL_Window* _sdlWindow;
};