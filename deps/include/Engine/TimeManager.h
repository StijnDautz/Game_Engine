#pragma once
#include <SDL\SDL.h>

class TimeManager {
	Uint32 previousMS;

public:
	void restart() {
		previousMS = SDL_GetTicks();
	}

	int deltatime() { return SDL_GetTicks() - previousMS; }
};