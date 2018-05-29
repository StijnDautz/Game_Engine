#pragma once
#include "Primitive.h"
#include "ColoredObj.h"
#include "Light.h"
#include "Engine\Color.h"
#include "Engine\Texture.h"

#include <vector>

class Scene
{
public:
	Scene() {}
	~Scene() {}

	RGBA32 Trace(Ray ray, int depth);
	RGBA32 TraceAndDebug(Texture* texture, Ray ray, int depth);
	void AddObject(ColoredObj obj) { _objects.push_back(obj); }
	void AddLight(Light l) { _lights.push_back(l); }
	void DrawDebug(Texture * texture);

private:
	std::vector<ColoredObj> _objects;
	std::vector<Light> _lights;
};