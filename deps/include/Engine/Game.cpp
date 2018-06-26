#include "Game.h"
#include "Core\CameraComponent.h"
#include "IO\Logger.h"

ResourceManager* resourceManager = new ResourceManager();
InputManager* inputManager = new InputManager();
TimeManager* timeManager = new TimeManager();

Game::Game() : _playing(true), camera(nullptr) {}
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
		_renderer.render(camera->GetComponent<CameraComponent>(), _gameObjects);

		// measure and print average ms/frame
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
}

void Game::quit()
{
	_playing = false;
}

void Game::Init()
{
	camera = new GameObject();
	camera->GetComponent<Transform>()->Translate(glm::vec3(0.0f, 0.0f, -10.0f));
	glm::mat4 perspective = glm::perspective(1.2f, 1.3f, .1f, 100.f);
	camera->AddComponent(new CameraComponent(perspective));
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