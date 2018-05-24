#pragma once
#include "Shader.h"
#include "Mesh.h"

#include <string>
#include <vector>

struct Shaderpack
{
public:
	GLuint id; //make this private?
	GLint textureLocation;

	Shaderpack(GLuint packID, GLint textureLoc) : id(packID), textureLocation(textureLoc) {}
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