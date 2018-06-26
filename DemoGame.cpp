#include "DemoGame.h"
#include <Engine\Rendering\Material\AssetFactories.h>
#include <Engine\Rendering\Material\MeshRenderer.h>
// Iostream - STD I/O Library
#include <iostream>

// Vector - STD Vector/Array Library
#include <vector>

// String - STD String Library
#include <string>

// fStream - STD File I/O Library
#include <fstream>

// Math.h - STD math Li
void DemoGame::Load()
{
	resourceManager->LoadShaderpack(
		"basic", 
		"Assets/Shaders/VertexShader.glsl", 
		"Assets/Shaders/fragmentShader.glsl"
	);
	resourceManager->LoadTexture("Assets/Textures/knight.png");
}

void DemoGame::Init()
{
	Game::Init();
	GameObject* screenquad = new GameObject();
	MeshRenderer* material = new MeshRenderer(
		resourceManager->GetShaderpack("basic"),
		resourceManager->GetTexture("Assets/Textures/knight.png"),
		MeshFactory::loadMeshFromFile("Debug/Assets/Meshes/quad.obj")
	);
	screenquad->AddComponent(material);
	AddGameObject(screenquad);
}