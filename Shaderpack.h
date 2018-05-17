#pragma once
#include "Shader.h"
#include "Mesh.h"

#include <string>
#include <vector>

class Shaderpack
{
public:
	GLuint id;
	GLint _textureLocation;

	Shaderpack(int packID, GLint textureLocation);
	~Shaderpack();

	void draw();
	void bindTexture();
	void AddMesh(Mesh* mesh);

private:
	std::vector<Mesh*> _meshes;
};