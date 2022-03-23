#include "IndicesBuffer.h"

IndicesBuffer::IndicesBuffer(std::vector<unsigned int> const& BufferData)
{
	glGenBuffers(1, &bufferIdentifier);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, bufferIdentifier);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, BufferData.size() * sizeof(unsigned int), BufferData.data(), GL_STATIC_DRAW);
}