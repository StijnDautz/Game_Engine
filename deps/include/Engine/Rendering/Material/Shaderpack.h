#pragma once
#include "Shader.h"

#include <string>
#include <vector>

struct Shaderpack
{
public:
	GLuint id; //make this private?
	GLint textureLocation;
	GLint toWorldLocation;
	GLint toScreenLocation;

	Shaderpack(GLuint packID) : id(packID) {
		// get and set texture uniform location
		textureLocation = glGetUniformLocation(packID, "tex");
		toWorldLocation = glGetUniformLocation(packID, "toWorld");
		toScreenLocation = glGetUniformLocation(packID, "toScreen");
	}
	~Shaderpack() {}

	void Bind()
	{
		glUseProgram(id);
	}

	void BindTexture(GLuint textureID)
	{
		// bind texture to texture unit 0
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, textureID);

		// set texture uniform
		glUniform1i(textureLocation, 0);
	}
};