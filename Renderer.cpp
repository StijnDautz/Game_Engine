#include "Renderer.h"
#include "Logger.h"
#include "MeshFactory.h"
#include "ShaderFactory.h"
#include "ShaderpackFactory.h"

#include <GL\glew.h>

Renderer::Renderer() : _shaderPack(nullptr) {}
Renderer::~Renderer() {}

void Renderer::init()
{
	_window = Window("RayTracerV1.1", 1280, 720);
	initShaders();
	initMeshes();
}

void Renderer::render()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glUseProgram(_shaderPack->id);

	_shaderPack->draw();
	_window.swap();
}

void Renderer::initShaders()
{
	Shader vertShader = ShaderFactory::create(GL_VERTEX_SHADER, "Shaders/vertexShader.glsl");
	Shader fragShader = ShaderFactory::create(GL_FRAGMENT_SHADER, "Shaders/fragmentShader.glsl");

	_shaderPack = ShaderpackFactory::create(
		std::vector<Shader> { vertShader, fragShader }, 
		std::vector<std::string> { "pos", "vertexColor" });
}

void Renderer::initMeshes()
{
	RGBA32 color0 = RGBA32(glm::vec3(0.8f, 0.6f, 0.3f));
	RGBA32 color1 = RGBA32(glm::vec3(0.1f, 0.2f, 0.9f));
	Vertex v0 = Vertex(glm::vec3(-1, -1, 0), color0);
	Vertex v1 = Vertex(glm::vec3(-1, 0, 0), color0);
	Vertex v2 = Vertex(glm::vec3(0, 0, 0), color0);
	Vertex v3 = Vertex(glm::vec3(0, -1, 0), color1);
	Vertex v4 = Vertex(glm::vec3(1, 1, 0), color1);

	Mesh* quad0 = MeshFactory::createQuad(v0, v1, v2, v3, GL_STATIC_DRAW);
	Mesh* triangle0 = MeshFactory::createTriangle(v1, v2, v4, GL_STATIC_DRAW);
	_shaderPack->AddMesh(quad0);
	_shaderPack->AddMesh(triangle0);
}