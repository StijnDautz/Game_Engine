#include "ShaderpackFactory.h"
#include "Logger.h"

ShaderpackFactory::ShaderpackFactory() {}
ShaderpackFactory::~ShaderpackFactory() {}

Shaderpack * ShaderpackFactory::create(std::vector<Shader> shaders, std::vector<std::string> attributes)
{
	int packID = glCreateProgram(); ;
	AttachShaders(shaders, packID);
	AddAttributes(attributes, packID);
	glLinkProgram(packID);
	HandleLinkingErrors(shaders, packID);
	return new Shaderpack(packID);
}

void ShaderpackFactory::AttachShaders(std::vector<Shader> shaders, int packID)
{
	for (int i = 0; i < shaders.size(); i++) {
		glAttachShader(packID, shaders[i].id);
	}
}

void ShaderpackFactory::AddAttributes(std::vector<std::string> attributes, int packID)
{
	for (int j = 0; j < attributes.size(); j++) {
		glBindAttribLocation(packID, j, attributes[j].c_str());
	}
}

void ShaderpackFactory::HandleLinkingErrors(std::vector<Shader> shaders, int packID)
{
	GLint isLinked = 0;
	glGetProgramiv(packID, GL_LINK_STATUS, (int *)&isLinked);
	if (isLinked == GL_FALSE)
	{
		GLint maxLength = 0;
		glGetProgramiv(packID, GL_INFO_LOG_LENGTH, &maxLength);

		// The maxLength includes the NULL character
		std::vector<GLchar> infoLog(maxLength);
		glGetProgramInfoLog(packID, maxLength, &maxLength, &infoLog[0]);

		// We don't need the program anymore.
		glDeleteProgram(packID);
		// Don't leak shaders either.
		for (int i = 0; i < shaders.size(); i++) {
			glDeleteShader(shaders[i].id);
		}
		fatalError("Failed to link shaders with id: " + packID);
	}

	// Always detach shaders after a successful link.
	for (int i = 0; i < shaders.size(); i++) {
		glDetachShader(packID, shaders[i].id);
	}
}