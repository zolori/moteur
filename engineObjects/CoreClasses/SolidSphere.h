#pragma once
#define _USE_MATH_DEFINES
#include "../../common/Header.h"
#include <cmath>
#include "IndicesBuffer.h"
#include <iostream>
class SolidSphere
{
public:
	SolidSphere(float radius, unsigned int rings, unsigned int sectors);

	std::vector<GLfloat> GetVertices() { return vertices; }
	std::vector<GLfloat> GetNormals() { return normals; }
	std::vector<GLfloat> GetTexcoords() { return texcoords; }
	std::vector<unsigned int> GetIndices() { return indices; }

protected:
	std::vector<GLfloat> vertices;
	std::vector<GLfloat> normals;
	std::vector<GLfloat> texcoords;
	std::vector<unsigned int> indices;
};

