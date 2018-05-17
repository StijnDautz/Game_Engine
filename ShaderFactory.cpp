#include "ShaderFactory.h"
#include "Logger.h"
#include "IOManager.h"

#include <vector>

Shader* ShaderFactory::create(GLenum type, std::string filePath)
{
	GLuint vertex_shader = glCreateShader(type);
	std::string file = ReadStringFromFile(filePath);
	const char *source = file.c_str();
	glShaderSource(vertex_shader, 1, &source, nullptr);
	glCompileShader(vertex_shader);
	HandleCompileErrors(vertex_shader, filePath);
	return new Shader(vertex_shader);
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