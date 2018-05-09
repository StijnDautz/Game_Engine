// More info on shader compilation at https://www.khronos.org/opengl/wiki/Shader_Compilation

#include "Shader.h"
#include "Logger.h"
#include "IOManager.h"

#include <vector>

Shader::Shader(GLenum type, std::string filePath) : _type(type)
{
	Compile(filePath);
}

Shader::Shader(GLenum type, std::string filePath, std::string* attributes, int count) : _type(type), attributes(attributes), attribCount(count)
{
	Compile(filePath);
}

Shader::~Shader()
{
	if (id != 0){
		glDeleteShader(id);
	}
}

void Shader::Compile(std::string filePath)
{
	id = glCreateShader(_type);
	std::string file = ReadFile(filePath);
	const char* ptr = file.c_str();
	glShaderSource(id, 1, &ptr, nullptr);
	glCompileShader(id);
	HandleCompileErrors(filePath);	
}

// this code was copied from the source at the top of this file
void Shader::HandleCompileErrors(std::string filePath)
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