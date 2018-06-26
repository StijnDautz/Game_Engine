#include "ShaderFactory.h"

#include <Engine\IO\IOManager.h>
#include <Engine\IO\Logger.h>
#include <vector>

Shader* ShaderFactory::create(GLenum type, std::string filePath)
{
	GLuint shaderID = glCreateShader(type);
	std::string file = ReadStringFromFile(filePath);
	const char *source = file.c_str();
	glShaderSource(shaderID, 1, &source, nullptr);
	glCompileShader(shaderID);
	HandleCompileErrors(shaderID, filePath);
	return new Shader(shaderID);
}

void ShaderFactory::HandleCompileErrors(GLuint id, std::string filePath)
{
	GLint status;
	glGetShaderiv(id, GL_COMPILE_STATUS, &status);
	if (status == GL_FALSE) {
		GLint length;
		glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
		std::vector<char> log(length);
		glGetShaderInfoLog(id, length, &length, &log[0]);
		fatalError(&log[0]);
	}
}