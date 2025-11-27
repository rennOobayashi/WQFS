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
	Shader postShader;
	Texture postTexture;
	unsigned int width, height;
	unsigned int msfbo, fbo;
	unsigned int rbo;
	unsigned int vao;

	void initRenderData();
public:
	bool shake;

	PostProcessing(Shader _shader, unsigned int	_width, unsigned int height);
	~PostProcessing() {};
	void BeginRender();
	void EndRender();
	void Render(float time);
};

#endif