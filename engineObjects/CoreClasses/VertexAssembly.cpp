#include "VertexAssembly.h"

VertexAssembly::VertexAssembly(std::vector<GLfloat> Position, std::vector<GLfloat> Normal, std::vector<GLfloat> Texcoords, std::vector<GLfloat> Color)
{
	position = Position;
	normal = Normal;
	texcoords = Texcoords;
	color = Color;
}
