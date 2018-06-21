#include "DemoGame.h"
#include <Engine\MeshFactory.h>



DemoGame::DemoGame()
{
}


DemoGame::~DemoGame()
{
}

void DemoGame::Load()
{
	resourceManager->LoadShader(GL_VERTEX_SHADER, "Assets/Shaders/VertexShader.glsl");
	resourceManager->LoadShader(GL_FRAGMENT_SHADER, "Assets/Shaders/fragmentShader.glsl");
}

void DemoGame::Init()
{

}