#include "ShaderFactory.h"
#include "Logger.h"
#include "IOManager.h"

#include <vector>


ShaderFactory::ShaderFactory() {}
ShaderFactory::~ShaderFactory() {}

Shader ShaderFactory::create(GLenum type, std::string filePath)
{
	GLuint id = glCreateShader(type);
	std::string file = ReadFile(filePath);
	const char* ptr = file.c_str();
	glShaderSource(id, 1, &ptr, nullptr);
	glCompileShader(id);
	HandleCompileErrors(id, filePath);
	return Shader(id);
}

void ShaderFactory::HandleCompileErrors(int id, std::string filePath)
{
	GLint isCompiled = 0;
	glGetShaderiv(id, GL_COMPILE_STATUS, &isCompiled);
	if (isCompiled == GL_FALSE)
	{
		GLint maxLength = 0;
		glGetShaderiv(id, GL_INFO_LOG_LENGTH, &maxLength);

		// The maxLength includes the NULL character
		std::vector<GLchar> errorLog(maxLength);
		glGetShaderInfoLog(id, maxLength, &maxLength, &errorLog[0]);

		// Provide the infolog in whatever manor you deem best.
		// Exit with failure.
		glDeleteShader(id); // Don't leak the shader.
		fatalError("Shader compile error at file: " + filePath);
	}
}