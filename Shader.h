#pragma once
#include <string>
#include <GL\glew.h>

class Shader
{
public:
	GLuint id;
	std::string* attributes;
	int attribCount;

	Shader(GLenum type, std::string filePath);
	Shader(GLenum type, std::string filePath, std::string* attributes, int count);
	~Shader();

	void Compile(const std::string filePath);

private:
	GLenum _type;

	void HandleCompileErrors(const std::string filePath);
};