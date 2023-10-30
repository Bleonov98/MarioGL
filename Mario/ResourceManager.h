#ifndef RESOURCE_H
#define RESOURCE_H

#include "Texture.h"
#include "Shader.h"

#include <string>
#include <map>

class ResourceManager
{
public:

	// shaders
	static Shader LoadShader(const char* vShader, const char* fShader, std::string name);

	static Shader GetShader(std::string name);

	// textures
	static Texture LoadTexture(const char* fileName, bool alpha, std::string name);

	static Texture GetTexture(std::string name);

private:

	ResourceManager() {};

	static std::map<std::string, Texture> textures;
	static std::map<std::string, Shader> shaders;

	static Texture LoadTextureFromFile(const char* fileName, bool alpha);
	static Shader LoadShaderFromFile(const char* vShader, const char* fShader);

};


#endif // !RESOURCE_H