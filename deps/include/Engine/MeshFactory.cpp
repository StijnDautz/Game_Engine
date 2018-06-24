#include "MeshFactory.h"
#include "Mesh.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <GL/GL.h>





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

Mesh * MeshFactory::createScreenQuad(float start, float end)
{
	std::vector<Vertex> vertices = {
		Vertex(glm::vec3(end  ,  1.0f, 0.0f), glm::vec2(1.0f, 1.0f)),  // vertex 0
		Vertex(glm::vec3(start,  1.0f, 0.0f), glm::vec2(0.0f, 1.0f)),  // vertex 1
		Vertex(glm::vec3(end  , -1.0f, 0.0f), glm::vec2(1.0f, 0.0f)),  // vertex 2
		Vertex(glm::vec3(start, -1.0f, 0.0f), glm::vec2(0.0f, 0.0f))   // vertex 3
	};

	std::vector<GLuint> indices{
		0,1,2, // first triangle
		2,1,3, // second triangle
	};

	return MeshFactory::create(vertices, indices, GL_STATIC_DRAW);
}


glm::vec3 getFaceIndices(std::string input) 
{
	int lastIndex = 0;
	int index = 0;
	glm::vec3 result;
	for (size_t i = 0; i < 3; i++)
	{
		lastIndex = index;
		while (input[index] != '/') 
		{
			index++;
		}
		result[i] = std::stof(input.substr(lastIndex, index));
	}
	return result;
}

void MeshFactory::AddMeshFromFile(Mesh mesh, std::string filePath)
{
	if (filePath.substr(filePath.size() - 4, 4) != ".obj") return;

	std::ifstream file(filePath);
	if (!file.is_open()) return;

	Mesh::MeshObject newMeshObject;
	
	std::string line;
	while (std::getline(file, line))
	{
		std::string inputType = line.substr(0,2);
		if (inputType == "v ") {
			std::istringstream v(line.substr(2));
			glm::vec3 vertex;
			std::string x, y, z;
			v>>x; v >> y; v >> z;
			vertex = glm::vec3(stof(x), stof(y), stof(z));
			newMeshObject.vertices.push_back(vertex);
			continue;
		}
		if (inputType == "vt") {
			std::istringstream vt(line.substr(3));
			glm::vec2 textureVertex;
			std::string x, y, z;
			vt >> x; vt >> y;
			textureVertex = glm::vec2(stof(x), stof(y));
			newMeshObject.textureVertices.push_back(textureVertex);
			continue;
		}
		if (inputType == "f ") {
			std::istringstream f(line.substr(0, 2));
			Mesh::Triangle newTriangle;
			std::string s1, s2, s3;
			f >> s1; f >> s2; f >> s3;
			glm::vec3 vertexInfo0 = getFaceIndices(s1);
			glm::vec3 vertexInfo1 = getFaceIndices(s2);
			glm::vec3 vertexInfo2 = getFaceIndices(s3);

			newTriangle.v0 = newMeshObject.vertices[vertexInfo0.x - 1]; //-1 because indexing starts at 1
			newTriangle.v1 = newMeshObject.vertices[vertexInfo1.x - 1]; //-1 because indexing starts at 1
			newTriangle.v2 = newMeshObject.vertices[vertexInfo2.x - 1]; //-1 because indexing starts at 1
			
			newTriangle.normal = newMeshObject.normalVertices[vertexInfo0.z - 1]; //Only use vertexInfo0 as the normal is equal for all point on the triangle
			
			newTriangle.texCoord0 = newMeshObject.textureVertices[vertexInfo0.y - 1];
			newTriangle.texCoord1 = newMeshObject.textureVertices[vertexInfo1.y - 1];
			newTriangle.texCoord2 = newMeshObject.textureVertices[vertexInfo2.y - 1];

			newMeshObject.triangles.push_back(newTriangle);
			continue;
		}
		else 
		{
			continue;
		}
	}

	mesh.meshes.push_back(newMeshObject);
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


