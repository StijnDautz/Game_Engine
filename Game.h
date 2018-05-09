#pragma once
#include "Renderer.h"

class Game
{
	enum Gamestate { PLAY, QUIT };

public:
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