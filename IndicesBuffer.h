#pragma once
#include "Buffer.h"
#include <vector>
class IndicesBuffer : private Buffer
{
public:
	/**
	* Constructor of the IndicesBuffer class, derived from the Buffer class
	* @params BufferData Data to put inside the buffer.
	* @param BufferType Type of the buffer to be draw. By default GL_ARRAY_BUFFER but if you're using glDrawElements
	* change it to GL_ELEMENT_ARRAY_BUFFER
	*/
	IndicesBuffer(std::vector<unsigned int> const& BufferData, GLenum BufferType = GL_ARRAY_BUFFER);
};

