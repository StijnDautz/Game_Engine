#pragma once
#include <GL\glew.h>
#include <list>

class Mesh
{
public:
	GLuint vaoID;

	Mesh(GLuint vao, char *fileName);
	~Mesh();

	void draw();

	struct triangle {
	public:
		glm::vec3 v0;
		glm::vec3 v1;
		glm::vec3 v2;
	};
	struct quad {
	public:
		glm::vec3 v0;
		glm::vec3 v1;
		glm::vec3 v2;
		glm::vec3 v3;
	};

	std::list<glm::vec3> vertices;
	std::list<triangle> triangles;
	std::list<quad> quads;
	
	
};