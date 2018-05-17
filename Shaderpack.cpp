//More info on shader linking at https://www.khronos.org/opengl/wiki/Shader_Compilation
#include "Shaderpack.h"

#include "Logger.h"
#include "Vertex.h"
#include "Game.h"

Shaderpack::Shaderpack(int packID, GLint textureLocation) : id(packID), _textureLocation(textureLocation) {}
Shaderpack::~Shaderpack() {}

void Shaderpack::draw()
{
	glUseProgram(id);

	bindTexture();
	for (int i = 0; i < _meshes.size(); i++) {
		_meshes[i]->draw();
	}

	glUseProgram(0);
}

void Shaderpack::bindTexture()
{
	// bind texture to texture unit 0
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, resourceManager->GetTexture("Textures/knight.png")->id);

	// set texture uniform
	glUniform1i(_textureLocation, 0);
}

void Shaderpack::AddMesh(Mesh* sprite)
{
	_meshes.push_back(sprite);
}