/* this object has to be allocated on the heap,
* as otherwise the destructor will be called.
* This causes the copied value to not contain a bufferobject,
* which was created in the glGenBuffers function*/
#include "Mesh.h"

Mesh::Mesh(GLuint id) : vboID(id) {}
//If you get a FRAME NOT IN MODULE error, this destructor was possibly accidentally called
Mesh::~Mesh()
{
	if (vboID != 0) {
		glDeleteBuffers(1, &vboID);
	}
}