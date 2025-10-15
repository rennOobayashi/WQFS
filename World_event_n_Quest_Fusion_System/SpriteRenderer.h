#ifndef SPRITERENDERER_H
#define SPRITERENDERER_H

#include "Shader.h"
#include "Texture.h"

#include <GLFW/glfw3.h>

class SpriteRenderer
{
private:
	Shader shader;
	unsigned int QAO;

	void init();
public:
	SpriteRenderer(Shader& shader);
	~SpriteRenderer();

	void DrawSprite(Texture &tex, glm::vec2 pos, glm::vec2 size = glm::vec2(10.0f), float rotate = 0.0f, glm::vec3 color = glm::vec3(1.0f), bool isSprite = false);
};

#endif