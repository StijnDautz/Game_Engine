#pragma once
#include "Shaderpack.h"
#include "Shader.h"

#include <vector>
#include <string>

class ShaderpackFactory
{
public:
	ShaderpackFactory();
	~ShaderpackFactory();

	static Shaderpack* create(std::vector<Shader> shaders, std::vector<std::string> attributes);

private:
	static void AttachShaders(std::vector<Shader> shaders, int packID);
	static void AddAttributes(std::vector<std::string> attributes, int packID);
	static void HandleLinkingErrors(std::vector<Shader> shaders, int packID);
};