#pragma once
#include <GL/glew.h>
class Texture
{
public:
	//Constructor of the Texture class.
	Texture();
	Texture(int n);
	//Constructor of the Texture class with parameters
	Texture(int Width, int Height);
	//Destructor of the Texture class.
	~Texture();
	/**
	* Getter for Texname
	* @return Return a GLuint 
	*/
	inline GLuint GetName() { return Texname; }
	/**
	* Getter for imgWidth
	* @return Return an int
	*/
	inline int GetWidth() { return imgWidth; }
	/**
	* Getter for imgHeight
	* @return Return an int
	*/
	inline int GetHeight() { return imgHeight; }
	/**
	* Load the image passed in the filepath bind it, and sets the parameter required to display the image correctly
	* 
	* @param filepath to the image you want to load
	* @return return true if the load was succesfull, else return false
	*/
	bool loadIMG(const char* filepath);
	/**
	* Call glActiveTexture and glBindTexture from OpenGL to use the texture for rendering
	*/
	void useIMG(int unit);

private:
	//Attribute

	GLuint Texname;
	int imgWidth;
	int imgHeight;
};

