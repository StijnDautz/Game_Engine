#pragma once
#include <SDL\SDL.h>
#include <iostream>

class FPSCounter {
	Uint32 previousMS = 0;
	int oldfps;
	int newfps;

public:
	void update() {
		if (SDL_GetTicks() - previousMS < 1000) {
			newfps++;
		}
		else {
			oldfps = newfps;
			newfps = 0;
			previousMS = SDL_GetTicks();
		}
	}

	void write() {
		std::cout << oldfps << std::endl;
	}
};