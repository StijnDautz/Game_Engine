#include "Mesh.h"

Mesh::Mesh(GLuint vao) : vaoID(vao) {}
//If you get a FRAME NOT IN MODULE error, this destructor was possibly accidentally called
Mesh::~Mesh()
{
	if (vaoID != 0) {
		glDeleteBuffers(1, &vaoID);
	}
}

void Mesh::draw()
{
	glBindVertexArray(vaoID);
	glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, nullptr);
}