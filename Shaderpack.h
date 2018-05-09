#pragma once
#include "Shader.h"
#include "Sprite.h"

#include <string>
#include <vector>

class Shaderpack
{
public:
	GLuint id;

	Shaderpack();
	Shaderpack(Shader* shaders);
	~Shaderpack();

	void draw();
	void AddSprite(Sprite* sprite);
	void RemoveSprite();

private:
	int _shaderCount;
	int _attributeCount;
	std::vector<Sprite*> _sprites;
	
	void CombineShaders(Shader* shaders);
	void AddAttributes(Shader* shaders);
	void LinkShaders(Shader* shaders);
	void HandleLinkingErrors(Shader* shaders);
};