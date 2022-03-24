#include "VertexAssembly.h"

VertexAssembly::VertexAssembly(std::vector<GLfloat> Position, std::vector<GLfloat> Normal, std::vector<GLfloat> Texcoords)
{
	position = Position;
	normal = Normal;
	texcoords = Texcoords;
}
