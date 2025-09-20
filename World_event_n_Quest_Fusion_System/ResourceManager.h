#ifndef RESOURCEMANAGER_H
#define RESOURCEMANAGER_H

#include "Shader.h"
#include "Texture.h"
#include "stb_image.h"

#include <iostream>
#include <map>
#include <string>
#include <sstream>
#include <fstream>

#include <glad/glad.h>

class ResourceManager
{
public:
	static std::map<std::string, Shader> shaders;
	static std::map<std::string, Texture> textures;

	static Shader LoadShader(const char* vShaderFile, const char* fShaderFileconst, char* gShaderFile, std::string name);
	static Shader GetShader(std::string name);
	static Texture LoadTexture(const char* file, bool alpha, std::string name);
	static Texture GetTexture(std::string file);
	static void Clear();
private:
	ResourceManager() {}
	static Shader LoadShaderFromFile(const char* vShaderFile, const char* fShaderFileconst, char* gShaderFile = nullptr);
	static Texture LoadTextureFromFile(const char *file, bool alpha);
};

#endif