#pragma once
#include "Primitive.h"
#include "ColoredObj.h"
#include "Light.h"
#include "Engine\Color.h"

#include <vector>

class Scene
{
public:
	Scene() : _objects(std::vector<ColoredObj>()), DEPTHCAP(1) {}
	~Scene() {}

	RGBA32 Trace(Ray ray, int depth);
	void AddObject(ColoredObj obj) { _objects.push_back(obj); }
	void AddLight(Light l) { _lights.push_back(l); }

private:
	const int DEPTHCAP;
	std::vector<ColoredObj> _objects;
	std::vector<Light> _lights;
};

