#pragma once
#include <GL\glew.h>

class Mesh
{
public:
	GLuint vaoID;

	Mesh(GLuint vao);
	~Mesh();

	void draw();
};