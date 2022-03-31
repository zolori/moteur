#include "VertexAssembly.h"

VertexAssembly::VertexAssembly(std::vector<GLfloat> Position,
								std::vector<unsigned int> Indices,
								std::vector<GLfloat> Normal,
								std::vector<GLfloat> Texcoords,
								std::vector<GLfloat> Color)
{
	position = Position;
	normal = Normal;
	texcoords = Texcoords;
	color = Color;
	indices = Indices;
}
