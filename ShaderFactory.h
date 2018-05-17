#pragma once
#include "Shader.h"
class ShaderFactory
{
public:
	static Shader* create(GLenum type, std::string filePath);
private:
	static void HandleCompileErrors(GLuint id, std::string filePath);
};