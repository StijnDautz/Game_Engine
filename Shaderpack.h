#pragma once
#include <string>
#include "Shader.h"

class Shaderpack
{
public:
	GLuint id;

	Shaderpack();
	Shaderpack(Shader* shaders);
	~Shaderpack();

private:
	int _count;
	int _attributeCount;
	
	void CombineShaders(Shader* shaders);
	void AddAttributes(Shader* shaders);
	void LinkShaders(Shader* shaders);
	void HandleLinkingErrors(Shader* shaders);
};

