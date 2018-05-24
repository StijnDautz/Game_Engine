#include "Game.h"

ResourceManager* resourceManager = new ResourceManager();
InputManager* inputManager = new InputManager();

Game::Game() : playing(true) {}
Game::~Game() {}

void Game::run()
{
	setup();
	load();
	init();
	
	while (playing) {
		update();
		renderer.render();
	}
}

void Game::CreateGameObject(RenderComponent rendercomp)
{
	renderer.AddRenderComponent(rendercomp);
}

void Game::quit()
{
	playing = false;
}

void Game::update()
{
	inputManager->Update();
}

void Game::setup()
{
	renderer.setup();
	inputManager->init();
}