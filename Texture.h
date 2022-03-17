#pragma once
#include <stdlib.h>
#include <stdio.h>
#include <GL/glew.h>
class Texture
{
public:
	//Constructor
	Texture();
	//Destructor
	~Texture();
	//Getter
	inline GLuint GetName() { return name; }
	inline int GetWidth() { return imgWidth; }
	inline int GetHeight() { return imgHeight; }
	//Function
	bool loadIMG(const char* filepath);
	void useIMG(int unit);

private:
	//Attribute
	GLuint name;
	int imgWidth;
	int imgHeight;
};

