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

	struct Triangle {
		glm::vec3 v0;
		glm::vec2 texCoord0;

		glm::vec3 v1;
		glm::vec2 texCoord1;

		glm::vec3 v2;
		glm::vec2 texCoord2;

		glm::vec3 normal;
	};
	struct MeshObject {
		std::vector<glm::vec3> vertices;
		std::vector<glm::vec2> textureVertices;
		std::vector<glm::vec3> normalVertices;
		std::vector<Triangle> triangles;
		//std::list<Quad> quads; //NOT YET SUPPORTED BY .OBJ PARSER
	};

	
	std::vector<MeshObject> meshes;
	Mesh(GLuint vao);
	~Mesh();

	void draw();
};