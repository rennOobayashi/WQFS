#ifndef POSTPROCESSING_H
#define POSTPROCESSING_H

#include <glad/glad.h>
#include <glm/glm.hpp>

#include "Texture.h"
#include "SpriteRenderer.h"
#include "Shader.h"


class PostProcessing
{
private:
	unsigned int msfbo, fbo;
	unsigned int rbo;
	unsigned int vao;

	void initRenderData();
public:

};

#endif