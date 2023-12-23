#include "Texture.h"

#include <glad/glad.h>

Texture::Texture()
	: width(0), height(0), internalFormat(GL_RGB), format(GL_RGB),
	wraps(GL_REPEAT), wrapt(GL_REPEAT), minFilter(GL_LINEAR), maxFilter(GL_LINEAR)
{
	glGenTextures(1, &id);
}

void Texture::generate(unsigned int width, unsigned int height, unsigned char* data) {
	this->width = width;
	this->height = height;

	glBindTexture(GL_TEXTURE_2D, id);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wraps);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrapt);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, minFilter);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, maxFilter);

	glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, width, height, 0, format, GL_UNSIGNED_BYTE, data);

	glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture::bind() const
{
	glBindTexture(GL_TEXTURE_2D, id);
}

float Texture::getWidthToHeightRatio() {
	return (float)width / (float)height;
}

float Texture::getHeightToWidthRatio() {
	return (float)height / (float)width;
}
