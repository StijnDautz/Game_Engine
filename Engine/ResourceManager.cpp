#include "ResourceManager.h"
#include "TextureFactory.h"
#include "ShaderFactory.h"

//MESH


void ResourceManager::AddMesh(std::string name, Mesh * mesh)
{
	_meshes.insert(std::make_pair(name, mesh));
}

//TEXTURE
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

//SHADER
Shader* ResourceManager::LoadShader(GLenum type, std::string filePath)
{
	Shader* shader = ShaderFactory::create(type, filePath);

	_shaders.insert(std::make_pair(filePath, shader));
	return shader;
}

//SHADERPACK
void ResourceManager::AddShaderpack(std::string name, Shaderpack * shaderpack)
{
	_shaderpacks.insert(std::make_pair(name, shaderpack));
}
