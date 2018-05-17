#include "Renderer.h"
#include "Logger.h"
#include "Game.h"
#include "MeshFactory.h"
#include "ShaderpackFactory.h"

#include <GL\glew.h>
#include <iostream>

Renderer::Renderer() : _shaderpack(nullptr) {}
Renderer::~Renderer() {}

void Renderer::init()
{
	_window = Window("TextureTest", 640, 480);

	// load assets
	resourceManager->LoadShader(GL_VERTEX_SHADER, "Shaders/vertexShader.glsl");
	resourceManager->LoadShader(GL_FRAGMENT_SHADER, "Shaders/fragmentShader.glsl");

	resourceManager->LoadTexture("Textures/knight.png");
	resourceManager->AddMesh("screenQuad", MeshFactory::createScreenQuad());

	// create program
	Shader * vertexshader = resourceManager->GetShader("Shaders/vertexShader.glsl");
	Shader * fragmentshader = resourceManager->GetShader("Shaders/fragmentShader.glsl");
	_shaderpack = ShaderpackFactory::create(vertexshader->id, fragmentshader->id);

	// link mesh to shaderpack
	_shaderpack->AddMesh(resourceManager->GetMesh("screenQuad"));
}

void Renderer::render()
{
	// clear first
	glClear(GL_COLOR_BUFFER_BIT);

	_shaderpack->draw();

	// check for errors
	GLenum error = glGetError();
	if (error != GL_NO_ERROR) {
		std::cerr << error << std::endl;
		fatalError("An error occured while rendering");
	}

	_window.swap();
}