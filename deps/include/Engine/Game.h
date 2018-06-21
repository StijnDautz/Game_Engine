#pragma once
#include "ResourceManager.h"
#include "InputManager.h"
#include "TimeManager.h"
#include "Renderer.h"
#include "FPSCounter.h"
#include "GameObject.h"

#include <vector>

extern ResourceManager* resourceManager;
extern InputManager* inputManager;
extern TimeManager* timeManager;

class Game
{
public:
	Game();
	~Game();
	
	void run();
	void quit();

	virtual void Load() {}
	virtual void Init() {}
	virtual void Update();

	void AddGameObject(GameObject* obj); // temporarily just the rendercomponent
	int GetScreenWidth() { return _renderer.window.width; }
	int GetScreenHeight() { return _renderer.window.height; }

private:
	bool _playing;

	void setup();
	Renderer _renderer;
	FPSCounter _fpscounter;

	std::vector<GameObject*> _gameObjects;
};