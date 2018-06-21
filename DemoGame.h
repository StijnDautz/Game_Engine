#pragma once
#include <Engine\Game.h>
class DemoGame : public Game
{
public:
	DemoGame();
	~DemoGame();


	void Load() override;
	void Init() override;
};

