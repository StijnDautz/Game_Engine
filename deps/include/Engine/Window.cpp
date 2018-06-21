#include "Window.h"
#include "Logger.h"

#include <GL\glew.h>

Window::Window() : width(0), height(0), _sdlWindow(nullptr) {}
Window::Window(std::string name, int w, int h)
{
	width = w;
	height = h;

	//init SDL
	SDL_Init(SDL_INIT_EVERYTHING);

	//create SDL window
	_sdlWindow = SDL_CreateWindow("RayTracerV1.0", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, w, h, SDL_WINDOW_OPENGL);
	if (_sdlWindow == nullptr) {
		fatalError("Window could not be created");
	}

	//create context
	SDL_GLContext context = SDL_GL_CreateContext(_sdlWindow);
	if (context == nullptr) {
		fatalError("Context could not be created");
	}

	//init glew
	if (glewInit() != GLEW_OK) {
		fatalError("Glew could not be initialized");
	}

	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
}
Window::~Window() {}

void Window::setDimensions(int w, int h)
{
	width = w;
	height = h;
}

void Window::SetBackgroundColor(float r, float g, float b)
{
	glClearColor(r, g, b, 1.0f);
}

void Window::swap()
{
	SDL_GL_SwapWindow(_sdlWindow);
}