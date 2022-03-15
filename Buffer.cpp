#include "Buffer.h"

/// <summary>
/// Constructor
/// </summary>
/// <param name="BufferData">Data to put in the buffer, a std::vector<GLfloat></param>
/// <param name="n">Index of the vector to be used by the shader</param>
/// <param name="s">Number of GLfloat to be used as a single point.
///					IE: 2 for a texture (U V) or 3 for a vertice (X Y Z)</param>
Buffer::Buffer(std::vector<GLfloat> const &BufferData, GLsizei n, GLint s)
{
	index = n;
	size = s;
	glGenBuffers(1, &bufferIdentifier);
	glBindBuffer(GL_ARRAY_BUFFER, bufferIdentifier);
	glBufferData(GL_ARRAY_BUFFER, BufferData.size() * sizeof(GLfloat), BufferData.data(), GL_STATIC_DRAW);
}

/// <summary>
/// Destructor
/// </summary>
Buffer::~Buffer()
{
	glDeleteBuffers(1, &bufferIdentifier);
}

/// <summary>
/// Draw the buffer
/// </summary>
void Buffer::DrawBuffer()
{
	glEnableVertexAttribArray(index);
	glBindBuffer(GL_ARRAY_BUFFER, bufferIdentifier);
	glVertexAttribPointer(
		index,
		size,
		GL_FLOAT,
		GL_FALSE,
		0,
		(void*)0
	);
}

/// <summary>
/// Disable the channel used to draw the buffer
/// </summary>
void Buffer::DisableBuffer()
{
	glDisableVertexAttribArray(index);
}
