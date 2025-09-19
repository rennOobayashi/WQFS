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
	static std::map<std::string, Shader> shaders;
	static std::map<std::string, Texture> textures;

	static Shader loadShader(const char* vShaderFile, const char* fShaderFileconst, char* gShaderFile, std::string name);
	static Texture loadTexture(const char* file, bool alpha);
	static Shader getShader(std::string name);
	static Texture getTexture(std::string file);
	static void clear();
private:
	ResourceManager() {}
	static Shader loadShaderFromFile(const char* vShaderFile, const char* fShaderFileconst, char* gShaderFile = nullptr);
	static Texture loadTextureFromFile(const char *file, bool alpha);
};

#endif