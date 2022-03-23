#include "Buffer.h"

Buffer::Buffer(std::vector<GLfloat> const &BufferData, GLsizei Location, GLint Size)
{
	location = Location;
	size = Size;
	glGenBuffers(1, &bufferIdentifier);
	glBindBuffer(GL_ARRAY_BUFFER, bufferIdentifier);
	glBufferData(GL_ARRAY_BUFFER, BufferData.size() * sizeof(GLfloat), BufferData.data(), GL_STATIC_DRAW);
}

Buffer::~Buffer()
{
	glDeleteBuffers(1, &bufferIdentifier);
}


void Buffer::BindBuffer()
{
	glEnableVertexAttribArray(location);
	glBindBuffer(GL_ARRAY_BUFFER, bufferIdentifier);
	glVertexAttribPointer(
		location,
		size,
		GL_FLOAT,
		GL_FALSE,
		0,
		(void*)0
	);
}

void Buffer::DisableBuffer()
{
	glDisableVertexAttribArray(location);
}
