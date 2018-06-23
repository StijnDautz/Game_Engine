#pragma once
#include "Vertex.h"
#include "Mesh.h"

#include <vector>

class MeshFactory
{
public:
	static Mesh * create(std::vector<Vertex> vertices, std::vector<GLuint> indices, GLenum usage);
	static Mesh * createScreenQuad(float start, float end);
	static Mesh * LoadMeshFromFile(std::string filePath);
	
private:
	static void fillVBO(std::vector<Vertex> vertices, GLenum usage);
	static void fillIBO(std::vector<GLuint> indices, GLenum usage);
	static void setAttribPointers();
};