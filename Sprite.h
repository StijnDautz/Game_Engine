#pragma once
#include "GLTexture.h"

#include <GL/glew.h>
#include <string>

//A 2D quad that can be rendered to the screen
class Sprite
{
public:
	GLuint vboID;

	Sprite() {}
	Sprite(float width, float height);
	Sprite(float width, float height, float x, float y);
	~Sprite();

	void init(float x, float y);

private:
	float _width;
	float _height;
	GLTexture _texture;
};