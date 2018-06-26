#pragma once
#include <string>
#include <Engine\Rendering\Material\Vertex.h>
#include <vector>

struct ObjResults {
	std::vector<Vertex> vertices;
	std::vector<GLuint> indices;

	ObjResults(std::vector<Vertex> v, std::vector<GLuint> i) : vertices(v), indices(i) {}
};

extern ObjResults LoadObjFile(std::string path);