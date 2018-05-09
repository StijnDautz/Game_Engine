#include "Sprite.h"
#include "Vertex.h"
#include "Quad.h"

Sprite::Sprite(float width, float height) : _width(width), _height(height), vboID(0) {}

//This constructor already takes a position, so the VBO can be initialized
Sprite::Sprite(float width, float height, float x, float y) : _width(width), _height(height), vboID(0) {
	init(x, y);
}

//If you get a FRAME NOT IN MODULE error, this destructor was possibly accidentally called
Sprite::~Sprite() {
	if (vboID != 0) {
		glDeleteBuffers(1, &vboID);
	}
}

void Sprite::init(float x, float y) {
	if (vboID == 0) {
		glGenBuffers(1, &vboID);
	}

	Quad quad = Quad(x, y, _width, _height);
	//Tell we are going to do something with this VBO
	glBindBuffer(GL_ARRAY_BUFFER, vboID);
	//Upload the data to the GPU
	glBufferData(GL_ARRAY_BUFFER, sizeof(quad), quad.vertexData, GL_STATIC_DRAW);
	//Tell openGL we are done, unnecessary but clean
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}