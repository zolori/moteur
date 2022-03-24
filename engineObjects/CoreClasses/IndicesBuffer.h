#pragma once
#include "Buffer.h"
#include <vector>
class IndicesBuffer : private Buffer
{
public:
	/**
	* Constructor of the IndicesBuffer class, derived from the Buffer class
	* @params BufferData Data to put inside the buffer.
	*/
	IndicesBuffer(std::vector<unsigned int> const& BufferData);
};

