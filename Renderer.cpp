#include "Renderer.h"
#include "Logger.h"

Renderer::Renderer() : _shaderPack(nullptr) {}
Renderer::~Renderer() {}

void Renderer::init()
{
	_window = new Window("RayTracerV1.1", 1280, 720);
	initShaders();
}

void Renderer::render()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glUseProgram(_shaderPack->id);

	_shaderPack->draw();
	_window->swap();
}

void Renderer::initShaders()
{
	Shader shaders[] = {
		Shader(GL_VERTEX_SHADER, "Shaders/vertexShader.glsl", new std::string[1]{ "pos" }, 1),
		Shader(GL_FRAGMENT_SHADER, "Shaders/fragmentShader.glsl"),
	};
	_shaderPack = new Shaderpack(shaders);
}