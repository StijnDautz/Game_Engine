#include "MeshFactory.h"
#include "Logger.h"
#include <stdlib.h>     /* abs */

Mesh* MeshFactory::create(std::vector<Vertex> vertices, std::vector<GLuint> indices, GLenum usage)
{
	GLuint vao;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	fillVBO(vertices, usage);
	fillIBO(indices, usage);
	setAttribPointers();

	// "unbind" vao
	glBindVertexArray(0);

	return new Mesh(vao);
}

/* Parameters should be within [-1.0f, +1.0f] */
Mesh * MeshFactory::createPanel(float start, float end)
{
	if (abs(start) > 1 || abs(end) > 1) fatalError("start: " + std::to_string(start) + " or " + "end: " + std::to_string(end) + "was not within the range[-1.0f, +1.0f]");
	std::vector<Vertex> vertices = {
		Vertex(glm::vec3( end  ,  1.0f, 0.0f), glm::vec2(1.0f, 1.0f)),  // vertex 0
		Vertex(glm::vec3( start,  1.0f, 0.0f), glm::vec2(0.0f, 1.0f)),  // vertex 1
		Vertex(glm::vec3( end  , -1.0f, 0.0f), glm::vec2(1.0f, 0.0f)),  // vertex 2
		Vertex(glm::vec3( start, -1.0f, 0.0f), glm::vec2(0.0f, 0.0f))   // vertex 3
	};

	std::vector<GLuint> indices{
		0,1,2, // first triangle
		2,1,3, // second triangle
	};

	return MeshFactory::create(vertices, indices, GL_STATIC_DRAW);
}

void MeshFactory::fillVBO(std::vector<Vertex> vertices, GLenum usage)
{
	GLuint vbo;
	// generate and bind the vbo
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);

	// fill with data
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], usage);
}

void MeshFactory::fillIBO(std::vector<GLuint> indices, GLenum usage)
{
	GLuint ibo;
	// generate and bind the index buffer object
	glGenBuffers(1, &ibo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);

	// fill with data
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint), &indices[0], usage);
}

void MeshFactory::setAttribPointers()
{
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (char*)offsetof(Vertex, position));

	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (char*)offsetof(Vertex, uv));
}