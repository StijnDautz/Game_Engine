#pragma once
#include <string>
#include <GL\glew.h>

class Shader
{
public:
	GLuint id;

	Shader(GLuint id);
	~Shader();
};