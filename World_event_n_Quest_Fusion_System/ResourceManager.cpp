#include "ResourceManager.h"

std::map<std::string, Shader> ResourceManager::shaders;
std::map<std::string, Texture> ResourceManager::textures;

Shader ResourceManager::loadShader(const char* vShaderFile, const char* fShaderFileconst, char* gShaderFile, std::string name) {
	shaders[name] = loadShaderFromFile(vShaderFile, fShaderFileconst, gShaderFile);
	return shaders[name];
}

Texture ResourceManager::loadTexture(const char* file, bool alpha) {
	textures[file] = loadTexture(file, alpha);
	return textures[file];
}

Shader ResourceManager::getShader(std::string name) {
	return shaders[name];
}

Texture ResourceManager::getTexture(std::string file) {
	return textures[file];
}

void ResourceManager::clear() {
	for (auto iter : shaders) {
		glDeleteProgram(iter.second.ID);
	}
	for (auto iter : textures) {
		glDeleteTextures(1, &iter.second.ID);
	}
}

Shader ResourceManager::loadShaderFromFile(const char* vShaderFile, const char* fShaderFileconst, char* gShaderFile) {
	std::string vertexCode;
	std::string fragmentCode;
	std::string geometryCode;

	try {
		std::ifstream vertexShaderFile(vShaderFile);
		std::ifstream fragmentShaderFile(fShaderFileconst);
		std::stringstream vShaderStream, fShaderStream;

		vShaderStream << vertexShaderFile.rdbuf();
		fShaderStream << fragmentShaderFile.rdbuf();

		vertexShaderFile.close();
		fragmentShaderFile.close();

		vertexCode = vShaderStream.str();
		fragmentCode = fShaderStream.str();

		if (gShaderFile != nullptr) {
			std::ifstream geometryShaderFile(gShaderFile);
			std::stringstream gShaderStream;

			gShaderStream << geometryShaderFile.rdbuf();
			geometryShaderFile.close();
			geometryCode = gShaderStream.str();

		}
	}
	catch (std::exception e) {
		std::cout << "ERROR::SHADER: Failed to read shader files" << std::endl;
	}

	const char* vShaderCode = vertexCode.c_str();
	const char* fShaderCode = fragmentCode.c_str();
	const char* gShaderCode = geometryCode.c_str();

	Shader shader;
	shader.Compile(vShaderCode, fShaderCode, gShaderFile != nullptr ? gShaderCode : nullptr);

	return shader;
}

Texture ResourceManager::loadTextureFromFile(const char* file, bool alpha) {
	Texture tex;

	if (alpha) {
		tex.internalFormat = GL_RGBA;
		tex.imageFormat = GL_RGBA;
	}
	int width, height, nrChannels;
	unsigned char* data = stbi_load(file, &width, &height, &nrChannels, 0);

	tex.Generate(width, height, data);
	return tex;
}