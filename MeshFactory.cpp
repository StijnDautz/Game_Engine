#include "MeshFactory.h"

MeshFactory::MeshFactory() {}
MeshFactory::~MeshFactory() {}

Mesh * MeshFactory::createTriangle(Vertex v0, Vertex v1, Vertex v2, GLenum usage)
{
	const int c = 3;
	Vertex vertices[c] = { v0, v1, v2 };
	return new Mesh(LoadVBO(vertices, c, usage));
}

Mesh * MeshFactory::createQuad(Vertex v0, Vertex v1, Vertex v2, Vertex v3, GLenum usage)
{
	const int c = 6;
	Vertex vertices[c] = { v0, v1, v2, v2, v3, v0 };
	return new Mesh(LoadVBO(vertices, c, usage));
}

GLuint MeshFactory::LoadVBO(Vertex * vertices, int count, GLenum usage)
{
	GLuint vboID;
	glGenBuffers(1, &vboID);
	//Tell we are going to do something with this VBO
	glBindBuffer(GL_ARRAY_BUFFER, vboID);
	//Upload the data to the GPU
	glBufferData(GL_ARRAY_BUFFER, count * sizeof(Vertex), vertices, usage);
	//Tell openGL we are done, unnecessary but clean
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	return vboID;
}