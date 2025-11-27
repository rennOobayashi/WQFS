#include "PostProcessing.h"

PostProcessing::PostProcessing(Shader _shader, unsigned int _width, unsigned int _height) 
	: postShader(_shader), width(_width), height(_height), postTexture(), shake(false) {
	glGenFramebuffers(1, &msfbo);
	glGenFramebuffers(1, &fbo);
	glGenRenderbuffers(1, &rbo);

	glBindFramebuffer(GL_FRAMEBUFFER, msfbo);
	glBindRenderbuffer(GL_RENDERBUFFER, rbo);
	glRenderbufferStorageMultisample(GL_RENDERBUFFER, 4, GL_RED, width, height);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_RENDERBUFFER, rbo);

	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
		std::cout << "ERROR::POSTPROCESSING failed to initialize MSFBO." << std::endl;
	}

	glBindFramebuffer(GL_FRAMEBUFFER, fbo);
	postTexture.Generate(width, height, NULL);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, postTexture.ID, 0);


	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
		std::cout << "ERROR::POSTPROCESSING failed to initialize MSFBO." << std::endl;
	}

	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	initRenderData();
	postShader.SetInt("scene", 0, true);

	float offset = 1.0f / 300.0f;
	float offsets[9][2] = {
		{-offset,  offset}, //top left
		{   0.0f,  offset}, //top center
		{ offset,  offset}, //top right
		{-offset,    0.0f}, //center left
		{   0.0f,    0.0f}, //center center
		{ offset,    0.0f}, //center right
		{-offset, -offset}, //bottom left
		{   0.0f, -offset}, //bottom center
		{ offset, -offset}  //bottom right
	};
	int edgeKernel[9]{
		-1, -1, -1,
		-1,  8, -1,
		-1, -1, -1
	};
	float blurKernel[9]{
		1.0f / 16.0f, 2.0f / 16.0f, 1.0f / 16.0f,
		2.0f / 16.0f, 4.0f / 16.0f, 2.0f / 16.0f,
		1.0f / 16.0f, 2.0f / 16.0f, 1.0f / 16.0f
	};

	glUniform2fv(glGetUniformLocation(postShader.ID, "offsets"), 9, (float*)offsets);
	glUniform1iv(glGetUniformLocation(postShader.ID, "edgeKernel"), 9, edgeKernel);
	glUniform1fv(glGetUniformLocation(postShader.ID, "blurKernel"), 9, blurKernel);

	//안되면 제거
	glBindRenderbuffer(GL_RENDERBUFFER, 0);
}

void PostProcessing::initRenderData() {
	unsigned int vbo;
	float vertices[] = {
		-1.0f, -1.0f, 0.0f, 0.0f,
		 1.0f,  1.0f, 1.0f, 1.0f,
		-1.0f,  1.0f, 0.0f, 1.0f,

		-1.0f, -1.0f, 0.0f, 0.0f,
		 1.0f, -1.0f, 1.0f, 0.0f,
		 1.0f,  1.0f, 1.0f, 1.0f,
	};

	glGenVertexArrays(1, &vao);
	glGenBuffers(1, &vbo);

	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindVertexArray(vao);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void PostProcessing::BeginRender() {
	glBindFramebuffer(GL_FRAMEBUFFER, msfbo);
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT);
}

void PostProcessing::EndRender() {
	glBindFramebuffer(GL_READ_FRAMEBUFFER, msfbo);
	glBindFramebuffer(GL_DRAW_FRAMEBUFFER, fbo);
	glBlitFramebuffer(0, 0, width, height, 0, 0, width, height, GL_COLOR_BUFFER_BIT, GL_NEAREST);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void PostProcessing::Render(float time) {
	postShader.use();
	postShader.SetFloat("time", time);
	postShader.SetInt("shake", shake);

	glActiveTexture(GL_TEXTURE0);
	postTexture.Bind();
	glBindVertexArray(vao);
	glDrawArrays(GL_TRIANGLES, 0, 6);
	glBindVertexArray(0);
}