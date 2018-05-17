#pragma once
#include "Shaderpack.h"
#include "Shader.h"

#include <vector>
#include <string>

class ShaderpackFactory
{
public:
	static Shaderpack * create(GLuint vertex_shader, GLuint fragment_shader);

private:
	static void handleLinkingErrors(GLuint packID);
};