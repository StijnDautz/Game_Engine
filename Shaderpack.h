#pragma once
#include "Shader.h"
#include "Mesh.h"

#include <string>
#include <vector>

class Shaderpack
{
public:
	GLuint id;

	Shaderpack(int id);
	~Shaderpack();

	void draw();
	void AddMesh(Mesh* mesh);

private:
	std::vector<Mesh*> _meshes;
};