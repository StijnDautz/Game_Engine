#include "Renderer.h"
#include "Logger.h"

Renderer::Renderer() {}
Renderer::Renderer(int width, int height) : _scrWidth(width), _scrHeight(height) {}
Renderer::~Renderer() {}

void Renderer::init()
{
	initOpenGL();
	initShaders();
	_sprite = new Sprite(1, 1, -1, -1);
}

void Renderer::render()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glUseProgram(_shaderPack.id);

	_sprite->draw();

	SDL_GL_SwapWindow(_window);
}

void Renderer::initOpenGL()
{
	//init SDL
	SDL_Init(SDL_INIT_EVERYTHING);
	_window = SDL_CreateWindow("RayTracerV1.0", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, _scrWidth, _scrHeight, SDL_WINDOW_OPENGL);
	if (_window == nullptr) {
		fatalError("Window could not be created");
	}

	SDL_GLContext context = SDL_GL_CreateContext(_window);
	if (context == nullptr) {
		fatalError("Context could not be created");
	}

	//init glew
	if (glewInit() != GLEW_OK) {
		fatalError("Glew could not be initialized");
	}

	//set OpenGL window properties
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	glClearColor(1.0f, 1.0f, 0.0f, 1.0f);
}

void Renderer::initShaders()
{
	Shader shaders[] = {
		Shader(GL_VERTEX_SHADER, "Shaders/vertexShader.glsl", new std::string[1]{ "pos" }, 1),
		Shader(GL_FRAGMENT_SHADER, "Shaders/fragmentShader.glsl"),
	};
	_shaderPack = Shaderpack(shaders);
}