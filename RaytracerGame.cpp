#include "RaytracerGame.h"

#include "Engine\MeshFactory.h"
#include "Engine\TextureFactory.h"
#include "Engine\ShaderpackFactory.h"

RaytracerGame::RaytracerGame() {}
RaytracerGame::~RaytracerGame() {}

void RaytracerGame::load()
{	
	resourceManager->LoadTexture("Textures/knight.png");

	resourceManager->LoadShader(GL_VERTEX_SHADER, "Shaders/vertexShader.glsl");
	resourceManager->LoadShader(GL_FRAGMENT_SHADER, "Shaders/fragmentShader.glsl");	
}

void RaytracerGame::init()
{
	Shader* vert = resourceManager->GetShader("Shaders/vertexShader.glsl");
	Shader* frag = resourceManager->GetShader("Shaders/fragmentShader.glsl");
	Shaderpack* basicpack = ShaderpackFactory::create(vert->id, frag->id);
	resourceManager->AddShaderpack("basic", basicpack);

	Texture* texture = TextureFactory::create(GetScreenWidth(), GetScreenHeight(), RGBA8(0, 120, 40, 255));
	resourceManager->AddTexture("screen", texture);

	Mesh* screenQuad = MeshFactory::createScreenQuad();
	resourceManager->AddMesh("screenQuad", screenQuad);

	RenderComponent screenRenderComp = RenderComponent(basicpack, texture, screenQuad);
	CreateGameObject(screenRenderComp);
}

void RaytracerGame::update()
{
	Game::update();
	if (inputManager->IsKeyDown(SDL_SCANCODE_ESCAPE)) {
		quit();
	}
}