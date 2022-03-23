#include "IndicesBuffer.h"

IndicesBuffer::IndicesBuffer(std::vector<unsigned int> const& BufferData, GLenum BufferType)
{
	bufferType = BufferType;
	glGenBuffers(1, &bufferIdentifier);
	glBindBuffer(bufferType, bufferIdentifier);
	glBufferData(bufferType, BufferData.size() * sizeof(unsigned int), BufferData.data(), GL_STATIC_DRAW);
}