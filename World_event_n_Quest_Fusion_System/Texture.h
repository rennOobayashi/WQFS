#ifndef TEXTURE_H
#define TEXTURE_H

#include <iostream>
#include <glad/glad.h>

class Texture
{
public:
	unsigned int ID;
	unsigned int tWidth, tHeight;
	unsigned int internalFormat, imageFormat;
	unsigned int wrapS, wrapT;
	unsigned int filterMin, filterMax;

	Texture();
	void Generate(unsigned int width, unsigned int height, unsigned char* data);
	void Bind() const;
};

#endif