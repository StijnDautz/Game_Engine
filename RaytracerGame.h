#pragma once
#include "Engine\Game.h"

class RaytracerGame : public Game
{
public:
	RaytracerGame();
	~RaytracerGame();

	void load() override;
	void init() override;
	void update() override;
};