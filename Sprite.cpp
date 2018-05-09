#include "Sprite.h"
#include "Vertex.h"
#include "Quad.h"

Sprite::Sprite(float width, float height) : _width(width), _height(height), _vboID(0) {}

//This constructor already takes a position, so the VBO can be initialized
Sprite::Sprite(float width, float height, float x, float y) : _width(width), _height(height), _vboID(0) {
	init(x, y);
}

//If you get a FRAME NOT IN MODULE error, this destructor was possibly accidentally called
Sprite::~Sprite() {
	if (_vboID != 0) {
		glDeleteBuffers(1, &_vboID);
	}
}

void Sprite::init(float x, float y) {
	if (_vboID == 0) {
		glGenBuffers(1, &_vboID);
	}

	Quad quad = Quad(x, y, _width, _height);
	//Tell we are going to do something with this VBO
	glBindBuffer(GL_ARRAY_BUFFER, _vboID);
	//Upload the data to the GPU
	glBufferData(GL_ARRAY_BUFFER, sizeof(quad), quad.vertexData, GL_STATIC_DRAW);
	//Tell openGL we are done, unnecessary but clean
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

// Draws the sprite to the screen
void Sprite::draw() {
	glBindBuffer(GL_ARRAY_BUFFER, _vboID);

	//Tell opengl what attribute arrays we need
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, position));
	//Draw the 6 vertices to the screen staring at 0
	glDrawArrays(GL_TRIANGLES, 0, 6);

	//Disable the vertex attrib arrays. This is not optional.
	glDisableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
}