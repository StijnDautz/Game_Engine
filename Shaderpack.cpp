//More info on shader linking at https://www.khronos.org/opengl/wiki/Shader_Compilation
/* This object has to be allocated on the heap, 
 * as otherwise the destructor will be called. 
 * This causes the copied value to not contain a shaderProgram, 
 * which was created in the glCreateProgram function*/
#include "Shaderpack.h"

#include "Logger.h"
#include "Vertex.h"

Shaderpack::Shaderpack(int packID) : id(packID) {}
Shaderpack::~Shaderpack() {}

void Shaderpack::draw()
{
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);

	//Tell opengl what attribute arrays we need	
	for (int i = 0; i < _meshes.size(); i++) {
		glBindBuffer(GL_ARRAY_BUFFER, _meshes[i]->vboID);
		//set vertexAttributePointers
		glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, position));
		glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, color));
		//Draw the 6 vertices to the screen staring at 0
		glDrawArrays(GL_TRIANGLES, 0, 6);
	}

	//Disable the vertex attrib arrays. This is not optional.
	glDisableVertexAttribArray(0);
	//this is optional, yet clean
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Shaderpack::AddMesh(Mesh* sprite)
{
	_meshes.push_back(sprite);
}