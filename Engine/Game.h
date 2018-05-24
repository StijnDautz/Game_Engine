#pragma once
#include "ResourceManager.h"
#include "InputManager.h"
#include "Renderer.h"

extern ResourceManager* resourceManager;
extern InputManager* inputManager;

class Game
{
public:
	Game();
	~Game();
	
	void run();
	void CreateGameObject(RenderComponent rendercomp); // temporarily just the rendercomponent
	void quit();

	virtual void load() {}
	virtual void init() {}
	virtual void update();

private:
	bool playing;

	void setup();
	Renderer renderer;
};