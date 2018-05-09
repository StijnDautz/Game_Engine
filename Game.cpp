#include "Game.h"
#include "Logger.h"

#include <iostream>
#include <SDL\SDL.h>

Game::Game() : _state(PLAY) {}
Game::~Game() {}

void Game::Run()
{
	InitSystems();
	while (_state != QUIT) {
		Update();
		_renderer.render();
	}
}

void Game::InitSystems()
{
	_renderer.init();
}

void Game::Update()
{
	BindInputToActions();
}

void Game::BindInputToActions()
{
	SDL_Event evnt;
	
	while (SDL_PollEvent(&evnt)) {
		switch (evnt.type) {
		case SDL_QUIT: _state = QUIT;
			break;
		}
	}
}