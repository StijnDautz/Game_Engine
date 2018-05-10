#pragma once
#include <GL\glew.h>

class Mesh
{
public:
	GLuint vboID;

	Mesh(GLuint id);
	~Mesh();
};