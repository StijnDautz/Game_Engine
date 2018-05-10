#pragma once
#include "Vertex.h"
#include "Mesh.h"

class MeshFactory
{
public:
	MeshFactory();
	~MeshFactory();

	static Mesh* createTriangle(Vertex v0, Vertex v1, Vertex v2, GLenum usage);
	static Mesh* createQuad(Vertex v0, Vertex v1, Vertex v2, Vertex v3, GLenum usage);

private:
	static GLuint LoadVBO(Vertex* vertices, int count, GLenum usage);
};