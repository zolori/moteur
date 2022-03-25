#include "Texture.h"
#include <../../common/stb_image.h>

Texture::Texture() 
{
	imgWidth = 0;
	imgHeight = 0;
	glGenTextures(1, &Texname);
}

Texture::Texture(int Width, int Height)
{
	imgWidth = Width;
	imgHeight = Height;
	glGenTextures(1, &Texname);
}

Texture::~Texture()
{
	glDeleteTextures(1, &Texname);
}

bool Texture::loadIMG(const char* filepath) 
{
	int width;
	int height;
	int comp;
	stbi_uc* pixels = stbi_load(filepath, &width, &height, &comp, 4);
	if (!pixels)
	{
		printf("ERROR:TEXTURE_LOADING_FAILED\n");
		return false;
	}
	glBindTexture(GL_TEXTURE_2D, Texname);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, pixels);

	stbi_image_free(pixels);

	imgWidth = width;
	imgHeight = height;

	return true;
}

void Texture::useIMG(int unit)
{
	glActiveTexture(GL_TEXTURE0 + unit);
	glBindTexture(GL_TEXTURE_2D, Texname);
}
