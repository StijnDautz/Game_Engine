#pragma once
#include "Core\Behaviour.h"
#include "Core\GameObject.h"
#include "Core\Transform.h"
#include "Rendering\Material\ResourceManager.h"
#include "Input\InputManager.h"
#include "Time\TimeManager.h"
#include "Time\FPSCounter.h"
#include "RendererV2.h"

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
	virtual void Init();
	virtual void Update();

	void AddGameObject(GameObject* obj); // temporarily just the rendercomponent
	int GetScreenWidth() { return _renderer.window.width; }
	int GetScreenHeight() { return _renderer.window.height; }

protected:
	GameObject * camera;

private:
	bool _playing;

	void setup();
	RendererV2 _renderer;
	FPSCounter _fpscounter;

	std::vector<GameObject*> _gameObjects;
};