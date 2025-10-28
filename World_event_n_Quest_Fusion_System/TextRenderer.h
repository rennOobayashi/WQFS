#ifndef TEXTRENDERER_H
#define TEXTRENDERER_H

#include <glad/glad.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <ft2build.h>
#include FT_FREETYPE_H

#include <iostream>
#include <map>

#include "ResourceManager.h"
#include "Texture.h"
#include "Shader.h"

struct Character {
	unsigned int ID;
	glm::ivec2 size;
	glm::ivec2 bearing;
	unsigned int advance;
};

class TextRenderer
{
private:
	std::map<char, Character> characters;
	unsigned int textureID;
	Shader tShader;
	unsigned int vao, vbo;

	void init(unsigned int width, unsigned int height);
public:
	TextRenderer(unsigned int width, unsigned int height);
	void load(std::string font, unsigned int fontSize);
	void renderText(std::string text, float x, float y, float scale, glm::vec3 color = glm::vec3(1.0f));
};

#endif