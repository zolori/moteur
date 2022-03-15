//Glew
#include <GL/glew.h>

//Miscellaneous
#include <vector>

class Buffer
{
public:
	//Constructor
	Buffer(std::vector<GLfloat> const &BufferData, GLsizei Index, GLint Size);
	//Destructor
	~Buffer();
	//Function
	void DrawBuffer();
	void DisableBuffer();
private:
	//Attribute
	GLuint bufferIdentifier;
	GLsizei index;
	GLint size;
};

