//Glew
#include <GL/glew.h>

//Miscellaneous
#include <vector>

class Buffer
{
public:
	/**
	* Constructor of the Buffer class.
	* @param BufferData Data to put inside the buffer.
	* @param Location Location of the buffer (should be equal to whatever Location you put in your shader).
	* @param Size Number of data to use while drawing the buffer (IE: 3 for Position/Normal(X Y Z) and 2 for UV(U V).
	*/
	Buffer(std::vector<GLfloat> const &BufferData, GLsizei Location, GLint Size);
	//Default constructor
	Buffer() = default;
	/**
	Destructor of the Buffer class
	*/
	~Buffer();
	//Function
	/**
	* Call glEnableVertexAttribArray, glBindBuffer and glVertexAttribPointer to enable, bind and attribute
	* the correct value to the buffer
	*/
	void BindBuffer();
	/**
	* Call glDisableVertexAttribArray to disable the buffer
	*/
	void DisableBuffer();
	//Attribute
	GLuint bufferIdentifier;
private:
	//Attribute
	GLsizei location;
	GLint size;
};

