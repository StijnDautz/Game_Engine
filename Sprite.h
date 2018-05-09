#pragma once
#include "GLTexture.h"

#include <GL/glew.h>
#include <string>

//A 2D quad that can be rendered to the screen
class Sprite
{
public:
	Sprite() {}
	Sprite(float width, float height);
	Sprite(float width, float height, float x, float y);
	~Sprite();

	void init(float x, float y);
	void draw();

private:
	float _x;
	float _y;
	float _width;
	float _height;
	GLuint _vboID;
	GLTexture _texture;
};