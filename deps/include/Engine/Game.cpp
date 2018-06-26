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
	Load();
	Init();
	
	while (_playing) {
		timeManager->restart();
		Update();
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

void Game::AddGameObject(GameObject* obj)
{
	_gameObjects.push_back(obj);

	// there is a flaw in this design. How can an object change material after this, as the renderer is only accessible in Game
	_renderer.AddRenderComponent(obj->renderComponent);
}

void Game::quit()
{
	_playing = false;
}

void Game::Update()
{
	inputManager->Update();
	for (unsigned int i = 0; i < _gameObjects.size(); i++) {
		_gameObjects[i]->Update();
	}
}

void Game::setup()
{
	_renderer.setup();
	inputManager->init();

}