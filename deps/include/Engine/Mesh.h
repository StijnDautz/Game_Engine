#pragma once
#include <GL\glew.h>
#include <glm\glm.hpp>
#include <vector>

class Mesh
{
	
	/*struct Quad {
	public:
		glm::vec3 v0;
		glm::vec3 v1;
		glm::vec3 v2;
		glm::vec3 v3;
	};*/

	

public:
	GLuint vaoID;

	struct VertexObject {
		glm::vec3 vertex;

		glm::vec2 texCoord;

		glm::vec3 normal;
	};
	struct MeshObject {
		std::vector<glm::vec3> vertices;
		std::vector<glm::vec2> textureVertices;
		std::vector<glm::vec3> normalVertices;
		std::vector<VertexObject> triangles;
		//std::list<Quad> quads; //NOT YET SUPPORTED BY .OBJ PARSER
	};

	
	std::vector<MeshObject> meshes;
	Mesh(GLuint vao);
	~Mesh();

	void draw();
};