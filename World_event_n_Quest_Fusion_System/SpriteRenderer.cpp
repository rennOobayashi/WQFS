#include "SpriteRenderer.h"

SpriteRenderer::SpriteRenderer(Shader& shader) {
	this->shader = shader;
	init();
}
SpriteRenderer::~SpriteRenderer() {
	glDeleteVertexArrays(1, &QAO);
}


void SpriteRenderer::init() {
	unsigned int QBO;
	float vertices[] = {
		//position //texture
		0.0f, 1.0f, 0.0f, 1.0f,
		1.0f, 0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 0.0f,

		0.0f, 1.0f, 0.0f, 1.0f,
		1.0f, 1.0f, 1.0f, 1.0f,
		1.0f, 0.0f, 1.0f, 0.0f
	};

	glGenVertexArrays(1, &QAO);
	glGenBuffers(1, &QBO);

	glBindBuffer(GL_ARRAY_BUFFER, QBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindVertexArray(QAO);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
	
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void SpriteRenderer::DrawSprite(Texture& tex, glm::vec2 pos, glm::vec2 size, float rotate, glm::vec3 color, bool isSprite) {
	shader.use();

	glm::mat4 model = glm::mat4(1.0f);
	model = glm::translate(model, glm::vec3(pos, 0.0f));

	model = glm::translate(model, glm::vec3(0.5f * size.x, 0.5f * size.y, 0.0f));
	model = glm::rotate(model, glm::radians(rotate), glm::vec3(0.0f, 0.0f, 1.0f));
	model = glm::translate(model, glm::vec3(-0.5f * size.x, -0.5f * size.y, 0.0f));

	model = glm::scale(model, glm::vec3(size, 1.0f));

	shader.SetMat4("model", model);
	shader.SetVec3("texColor", color);
	shader.SetInt("isSprite", isSprite);

	glActiveTexture(GL_TEXTURE0);
	tex.Bind();

	glBindVertexArray(QAO);
	glDrawArrays(GL_TRIANGLES, 0, 6);
	glBindVertexArray(0);
}