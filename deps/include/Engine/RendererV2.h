#pragma once
#include "Core\GameObject.h"
#include "Core\CameraComponent.h"
#include "Rendering\Window.h"

#include <vector>
#include <GL\glew.h>

class RendererV2
{
public:
	RendererV2() {}
	~RendererV2() {}

	Window window;

	void setup();
	void render(CameraComponent* camera, std::vector<GameObject*> objects);
	void checkErrors();
};