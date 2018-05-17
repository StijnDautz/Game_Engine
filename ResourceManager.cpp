#include "ResourceManager.h"
#include "TextureFactory.h"
#include "ShaderFactory.h"

void ResourceManager::AddMesh(std::string name, Mesh * mesh)
{
	_meshes.insert(std::make_pair(name, mesh));
}

//TEXTURES
Texture * ResourceManager::LoadTexture(std::string filePath)
{
	return InsertTexture(filePath, TextureFactory::createFromFile(filePath));
}

Texture * ResourceManager::AddTexture(std::string name, std::vector<unsigned char> pixels, int width, int height)
{
	return InsertTexture(name, TextureFactory::create(pixels, width, height));
}
//helper function
Texture* ResourceManager::InsertTexture(std::string name, Texture* texture)
{
	_textures.insert(std::make_pair(name, texture));
	return texture;
}

//SHADERS
Shader* ResourceManager::LoadShader(GLenum type, std::string filePath)
{
	Shader* shader = ShaderFactory::create(type, filePath);

	_shaders.insert(std::make_pair(filePath, shader));
	return shader;
}