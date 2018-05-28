#pragma once
#include "Shaderpack.h"
#include "Window.h"
#include "Texture.h"

#include <map>
#include <vector>

typedef std::map<Texture*, std::vector<Mesh*>> Texture_Mesh_Combo;
typedef std::map<Shaderpack*, Texture_Mesh_Combo> Rendermap;

struct RenderComponent {
	Shaderpack* pack;
	Texture* texture;
	Mesh* mesh;

	RenderComponent(Shaderpack* sp, Texture* t, Mesh* m) : pack(sp), texture(t), mesh(m) {}
	~RenderComponent() {}
};

class Renderer
{
public:
	Renderer();
	~Renderer();

	Window window;

	void setup();
	void render();
	void AddRenderComponent(RenderComponent obj);
	void RemoveRenderComponent(RenderComponent obj) {}

private:
	Rendermap renderMap;
};