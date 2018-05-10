#pragma once
#include "Shader.h"
class ShaderFactory
{
public:
	ShaderFactory();
	~ShaderFactory();

	static Shader create(GLenum type, std::string filePath);

private:
	static void HandleCompileErrors(int id, std::string filePath);
};