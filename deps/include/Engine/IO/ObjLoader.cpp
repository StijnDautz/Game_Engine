#include "ObjLoader.h"
#include <fstream>
#include <sstream>
#include <Engine\IO\Logger.h>
#include <map>
#include <stdlib.h>     /* atoi */

glm::vec2 Read2(std::string line) {
	std::istringstream s(line.substr(2));
	glm::vec3 p; s >> p.x; s >> p.y;
	return p;
}

glm::vec3 Read3(std::string line) {
	std::istringstream s(line.substr(2));
	glm::vec3 p; s >> p.x; s >> p.y; s >> p.z;
	return p;
}

bool GetIndex(std::vector<Vertex> vertices, Vertex v1, GLuint &index) {
	Vertex v2;
	for (size_t i = 0; i < vertices.size(); i++) {
		v2 = vertices[i];
		if (v1.position == v2.position && v1.uv == v2.uv) {
			index = (GLuint)i;
			return true;
		}
	}
	return false;
}

int convertIndex(std::string substring, int i) {
	return substring[i] - '0' - 1;
}

ObjResults LoadObjFile(std::string path)
{
	std::vector<glm::vec3> v;
	std::vector<glm::vec2> vt;
	std::vector<glm::vec3> vn;
	std::vector<Vertex> vertices;
	std::vector<GLuint> indices;

	std::ifstream stream(path);
	if (!stream.is_open()) {
		fatalError("Cannot open " + path);
	}

	std::string line;
	std::string prefix;
	GLuint index;
	while (std::getline(stream, line))
	{
		prefix = line.substr(0, 2);
		if (prefix == "v ")	{
			v.push_back(Read3(line));
		} else if (prefix == "vt") {
			vt.push_back(Read2(line));
		} else if (prefix == "vn") {
			// read and normalize the vector
			glm::vec3 n = glm::normalize(Read3(line));
			vn.push_back(n);
		} else if (line.substr(0, 2) == "f ")
		{
			std::string substring = line.substr(2);
			std::vector<int> values;
			std::string value;
			for (size_t i = 0; i < substring.size(); i++) {
				int j = i;
				while (j < substring.size() && substring[j] != ' ' && substring[j] != '/') {
					value += substring[j++];
				}
				
				// an empty field
				if (substring[j-1] == '/' && substring[j] == '/') {													
					// -1 is applied because indices in OBJ files start from 1
					fatalError("field was empty, no support for this yet");
				}// a value
				else if (!value.empty()) {
					values.push_back(atoi(value.c_str()) - 1);
					value = "";
				}
				// else a space
			}

			std::vector<Vertex> tempvertices;
			switch (values.size()) {
				// position/uv
				case 6: 
					fatalError("this case was not implemented position/uv/normal");
					break;
				// position/uv/normal
				case 9:
					for (int i = 0; i < 9; i += 3) {
						tempvertices.push_back(Vertex(v[values[i]], vt[values[i + 1]], vn[values[i+2]]));
					}
					break;
			}

			for (size_t i = 0; i < tempvertices.size(); i++) {
				// returns true if the vertex already is inside the container
				// else sets the index equal to the new one
				if (GetIndex(vertices, tempvertices[i], index)) {
					indices.push_back(index);
				}
				else {
					indices.push_back(vertices.size());
					vertices.push_back(tempvertices[i]);
				}
			}
		}
	}
	return ObjResults(vertices, indices);
}