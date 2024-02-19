#pragma once
class Texture
{
public:
	unsigned int id;
	unsigned int width, height;

	unsigned int wraps, wrapt;
	unsigned int minFilter, maxFilter;
	unsigned int format, internalFormat;

	Texture();
	void generate(unsigned int width, unsigned int height, unsigned char* data);
	void bind() const;
	void bindUnit(int i) const;
	
	float getWidthToHeightRatio();
	float getHeightToWidthRatio();
};

