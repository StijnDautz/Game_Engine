// More info on shader compilation at https://www.khronos.org/opengl/wiki/Shader_Compilation
#include "Shader.h"
#include "Logger.h"
#include <vector>

Shader::Shader(GLuint ID) : id(ID) {}
Shader::~Shader()
{
	if (id != 0){
		glDeleteShader(id);
	}
}