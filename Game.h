#pragma once
#include "Renderer.h"
#include "ResourceManager.h"

extern ResourceManager* resourceManager;

class Game
{
public:
	enum Gamestate { PLAY, QUIT };

	Game();
	~Game();
	void Run();

private:
	Gamestate _state;
	Renderer _renderer;

	void InitSystems();
	void Update();
	void BindInputToActions();
};