//More info on shader linking at https://www.khronos.org/opengl/wiki/Shader_Compilation

#include "Shaderpack.h"
#include "Logger.h"
#include "Vertex.h"

Shaderpack::Shaderpack() {}

Shaderpack::Shaderpack(Shader* shaders) : _shaderCount(2), _attributeCount(0), id(0)
{
	CombineShaders(shaders);
	AddAttributes(shaders);
	LinkShaders(shaders);
	_sprites.push_back(new Sprite(1, 1, -1, -1));
}

Shaderpack::~Shaderpack() {}

void Shaderpack::draw()
{
	glEnableVertexAttribArray(0);

	//Tell opengl what attribute arrays we need	
	for (int i = 0; i < _sprites.size(); i++) {
		glBindBuffer(GL_ARRAY_BUFFER, _sprites[i]->vboID);
		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, position));
		//Draw the 6 vertices to the screen staring at 0
		glDrawArrays(GL_TRIANGLES, 0, 6);
	}

	//Disable the vertex attrib arrays. This is not optional.
	glDisableVertexAttribArray(0);
	//this is optional, yet clean
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Shaderpack::AddSprite(Sprite* sprite)
{
	_sprites.push_back(sprite);
}

void Shaderpack::CombineShaders(Shader* shaders)
{
	id = glCreateProgram();
	for (int i = 0; i < _shaderCount; i++) {
		glAttachShader(id, shaders[i].id);
	}
}

void Shaderpack::AddAttributes(Shader* shaders)
{
	for (int i = 0; i < _shaderCount; i++) {
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

//this function contains code, copied from the source at the top of this file
void Shaderpack::HandleLinkingErrors(Shader* shaders)
{
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
		for (int i = 0; i < _shaderCount; i++) {
			glDeleteShader(shaders[i].id);
		}
		fatalError("Failed to link shaders with id: " + id);
	}

	// Always detach shaders after a successful link.
	for (int i = 0; i < _shaderCount; i++) {
		glDetachShader(id, shaders[i].id);
	}
}