#pragma once
#include "Engine\Game.h"
#include "Engine\Transform.h"
#include "Scene.h"

class RaytracerGame : public Game
{
public:
	RaytracerGame();
	~RaytracerGame();

	void load() override;
	void init() override;
	void update() override;

private:
	float focalLength;
	Transform camera;
	int resolutionX;
	int resolutionY;
	Scene _scene;
	Texture* displayed;
	Texture* image;
	Texture* debug;
};