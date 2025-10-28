#include "TextRenderer.h"

TextRenderer::TextRenderer(unsigned int width, unsigned int height) {
	init(width, height);
}

void TextRenderer::init(unsigned int width, unsigned int height) {
	tShader = ResourceManager::LoadShader("verfrag/text_vertex.vs", "verfrag/text_fragment.fs", nullptr, "text");
	tShader.SetMat4("projection", glm::ortho(0.0f, float(width), float(height), 0.0f), true);
	tShader.SetInt("text", 0);

	glGenVertexArrays(1, &vao);
	glGenBuffers(1, &vbo);
	glBindVertexArray(vao);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 6 * 4, NULL, GL_DYNAMIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void TextRenderer::load(std::string font, unsigned int fontSize) {
	characters.clear();

	FT_Library ft;
	FT_Face face;

	if (FT_Init_FreeType(&ft)) {
		std::cout << "ERROR::FREETYPE: Could not init FreeType Library" << std::endl;
	}

	if (FT_New_Face(ft, font.c_str(), 0, &face)) {
		std::cout << "ERROR::FREETYPE: Failed to load font" << std::endl;
	}

	FT_Set_Pixel_Sizes(face, 0, fontSize);
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

	for (GLubyte c = 0; c < 128; c++) {
		if (FT_Load_Char(face, c, FT_LOAD_RENDER)) {
			std::cout << "ERROR::FREETYPE: Failed to load Glyph" << std::endl;
			continue;
		}
		unsigned int texture;

		glGenTextures(1, &texture);
		glBindTexture(GL_TEXTURE_2D, texture);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RED,
			face->glyph->bitmap.width, 
			face->glyph->bitmap.rows, 
			0, GL_UNSIGNED_BYTE, GL_RED, 
			face->glyph->bitmap.buffer);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		Character character = {
			texture,
			glm::ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows),
			glm::ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top),
			face->glyph->advance.x };

		characters.insert(std::pair<char, Character>(c, character));
	}

	FT_Done_Face(face);
	FT_Done_FreeType(ft);
}

void TextRenderer::renderText(std::string text, float x, float y, float scale, glm::vec3 color) {
	tShader.use();
	tShader.SetVec3("textColor", color);

	glActiveTexture(GL_TEXTURE0);
	glBindVertexArray(vao);

	std::string::const_iterator iter;

	for (iter = text.begin(); iter != text.end(); ++iter) {
		Character c = characters[*iter];

		float posX = x + c.bearing.x * scale;
		float posY = y + (characters['H'].bearing.y - c.bearing.y) * scale;

		float w = c.size.x + scale;
		float h = c.size.y + scale;

		float vertices[6][4] = {
			{posX    , posY + h, 0.0f, 1.0f},
			{posX + w, posY    , 1.0f, 0.0f},
			{posX    , posY    , 0.0f, 0.0f},

			{posX    , posY + h, 0.0f, 1.0f},
			{posX + w, posY + h, 1.0f, 1.0f},
			{posX + w, posY    , 1.0f, 0.0f},
		};

		glBindTexture(GL_TEXTURE_2D, c.ID);
		glBindBuffer(GL_ARRAY_BUFFER, vbo);
		glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
		glBindBuffer(GL_ARRAY_BUFFER, 0);

		glDrawArrays(GL_TRIANGLES, 0, 6);
		//렌더 안되면 for 밖으로

		x += (c.advance >> 6) * scale;
	}

	glBindVertexArray(0);
	glBindTexture(GL_TEXTURE_2D, 0);
}
