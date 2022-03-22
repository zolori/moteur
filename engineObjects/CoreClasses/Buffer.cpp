#include "Buffer.h"

Buffer::Buffer(std::vector<GLfloat> const &BufferData, GLsizei Location, GLint Size, GLenum BufferType)
{
	location = Location;
	size = Size;
	bufferType = BufferType;
	glGenBuffers(1, &bufferIdentifier);
	glBindBuffer(bufferType, bufferIdentifier);
	glBufferData(bufferType, BufferData.size() * sizeof(GLfloat), BufferData.data(), GL_STATIC_DRAW);
}

Buffer::~Buffer()
{
	glDeleteBuffers(1, &bufferIdentifier);
}


void Buffer::BindBuffer()
{
	glEnableVertexAttribArray(location);
	glBindBuffer(bufferType, bufferIdentifier);
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
