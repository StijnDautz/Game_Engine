#pragma once
#include <Engine\Core\Behaviour.h>
#include "Shaderpack.h"
#include "Texture.h"
#include "Mesh.h"

class MeshRenderer : public Behaviour {
public:
	Shaderpack* pack;
	Texture* texture;
	Mesh* mesh;

	MeshRenderer() : pack(nullptr), texture(nullptr), mesh(nullptr) {}
	MeshRenderer(Shaderpack* p, Texture* t, Mesh* m) : pack(p), texture(t), mesh(m) {}
	~MeshRenderer() {}
};