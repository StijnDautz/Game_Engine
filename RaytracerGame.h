#pragma once
#include "Engine\Game.h"
#include "Engine\Transform.h"
#include "Scene.h"

class RaytracerGame : public Game
{
public:
	RaytracerGame() : debuggerEnabled(true), resolutionX(512), resolutionY(512), focalLength(1) {}
	~RaytracerGame() {}

	void load() override;
	void init() override;
	void update() override;


private:
	bool debuggerEnabled;
	float focalLength;
	Transform camera;
	int resolutionX;
	int resolutionY;
	Scene _scene;
	Texture* displayed;
	Texture* image;
	Texture* debug;

	void ComputePart(int x, glm::vec3 topleft, glm::vec3 xInterval, glm::vec3 yInterval);
	void DebugLoop(glm::vec3 topleft, glm::vec3 xInterval, glm::vec3 yInterval);
	void SetFocallength();
};