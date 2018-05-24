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
	void quit();

	virtual void load() {}
	virtual void init() {}
	virtual void update();

	void CreateGameObject(RenderComponent rendercomp); // temporarily just the rendercomponent
	int GetScreenWidth() { return renderer.window.width; }
	int GetScreenHeight() { return renderer.window.height; }

private:
	bool playing;

	void setup();
	Renderer renderer;
};