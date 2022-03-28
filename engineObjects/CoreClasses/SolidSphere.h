#pragma once
#define _USE_MATH_DEFINES
#include "../../common/Header.h"
#include <cmath>
#include "IndicesBuffer.h"
class SolidSphere
{
public:
	SolidSphere(float radius, unsigned int rings, unsigned int sectors);

	void Draw();

protected:
	std::vector<GLfloat> vertices;
	std::vector<GLfloat> normals;
	std::vector<GLfloat> texcoords;
	std::vector<unsigned int> indices;

	unsigned int VAO;
};

