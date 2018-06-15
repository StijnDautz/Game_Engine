#include "Game.h"

ResourceManager* resourceManager = new ResourceManager();
InputManager* inputManager = new InputManager();
TimeManager* timeManager = new TimeManager();

Game::Game() : _playing(true) {}
Game::~Game() {}

int ms = 0;
int c = 0;
const int SAMPLECOUNT = 10;

void Game::run()
{
	setup();
	load();
	init();
	
	while (_playing) {
		timeManager->restart();
		update();
		_renderer.render();
		if (++c < SAMPLECOUNT) {
			ms += timeManager->deltatime();
		}
		else {
			std::cout << ms / SAMPLECOUNT << std::endl;
			c = 0; ms = 0;
		}
	}
}

void Game::CreateGameObject(RenderComponent rendercomp)
{
	_renderer.AddRenderComponent(rendercomp);
}

void Game::quit()
{
	_playing = false;
}

void Game::update()
{
	inputManager->Update();
}

void Game::setup()
{
	_renderer.setup();
	inputManager->init();
}