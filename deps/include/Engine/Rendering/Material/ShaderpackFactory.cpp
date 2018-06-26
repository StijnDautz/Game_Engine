#include "ShaderpackFactory.h"

#include <Engine\IO\Logger.h>

Shaderpack * ShaderpackFactory::create(GLuint vertshader, GLuint fragshader)
{
	GLuint packID = glCreateProgram();

	// attach shaders
	glAttachShader(packID, vertshader);
	glAttachShader(packID, fragshader);

	// link the program and check for errors
	glLinkProgram(packID);
	handleLinkingErrors(packID);

	//TODO add ToWorld and ToScreen
	return new Shaderpack(packID);
}

void ShaderpackFactory::handleLinkingErrors(GLuint packID) {
	GLint status;
	glGetProgramiv(packID, GL_LINK_STATUS, &status);
	if (status == GL_FALSE) {
		GLint length;
		glGetProgramiv(packID, GL_INFO_LOG_LENGTH, &length);
		std::vector<char> log(length);
		glGetProgramInfoLog(packID, length, &length, &log[0]);
		fatalError("could not link shaders in shaderpack: " + packID);
	}
}