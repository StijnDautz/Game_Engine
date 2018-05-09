// More info on shader linking at https://www.khronos.org/opengl/wiki/Shader_Compilation

#include "Shaderpack.h"
#include "Logger.h"

#include <string>
#include <vector>

Shaderpack::Shaderpack() {}

Shaderpack::Shaderpack(Shader* shaders) : _count(2), _attributeCount(0), id(0)
{
	CombineShaders(shaders);
	AddAttributes(shaders);
	LinkShaders(shaders);
}

Shaderpack::~Shaderpack()
{
}

void Shaderpack::CombineShaders(Shader* shaders)
{
	id = glCreateProgram();
	for (int i = 0; i < _count; i++) {
		glAttachShader(id, shaders[i].id);
	}
}

void Shaderpack::AddAttributes(Shader* shaders)
{
	for (int i = 0; i < _count; i++) {
		for (int j = 0; j < shaders[i].attribCount; j++) {
			glBindAttribLocation(id, _attributeCount++, shaders[i].attributes[j].c_str());
		}
	}
}

void Shaderpack::LinkShaders(Shader * shaders)
{
	glLinkProgram(id);
	HandleLinkingErrors(shaders);
}

// this function contains code, copied from the source at the top of this file
void Shaderpack::HandleLinkingErrors(Shader* shaders)
{
	// Note the different functions here: glGetProgram* instead of glGetShader*.
	GLint isLinked = 0;
	glGetProgramiv(id, GL_LINK_STATUS, (int *)&isLinked);
	if (isLinked == GL_FALSE)
	{
		GLint maxLength = 0;
		glGetProgramiv(id, GL_INFO_LOG_LENGTH, &maxLength);

		// The maxLength includes the NULL character
		std::vector<GLchar> infoLog(maxLength);
		glGetProgramInfoLog(id, maxLength, &maxLength, &infoLog[0]);

		// We don't need the program anymore.
		glDeleteProgram(id);
		// Don't leak shaders either.
		for (int i = 0; i < _count; i++) {
			glDeleteShader(shaders[i].id);
		}
		fatalError("Failed to link shaders with id: " + id);
	}

	// Always detach shaders after a successful link.
	for (int i = 0; i < _count; i++) {
		glDetachShader(id, shaders[i].id);
	}
}