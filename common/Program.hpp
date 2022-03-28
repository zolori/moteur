#pragma once
#include "functions.hpp"
#include "../engineObjects/Components/Light.hpp"
class Program {

private:
	GLuint  num;
	std::vector<GLuint> uniformVariable;
public:
	Program(const char* directory, const char* vertexShader, const char* fragmentShader);
	Program(const char* directory, const char* vertexShader, const char* fragmentShader, int numberOfLights);
	void Use();
	GLuint GetNum();

	//Generic functions
	void AddUniformVar(const char* name);
	void SetFloat(GLuint uniform, float value);
	void SetVector(GLuint uniform, vec3 vector);
	void SetMatrix4(GLuint uniform, GLsizei count, GLboolean transpose, const GLfloat* value);

	//Specific functions
	void BindTexture(GLuint texture);

	void SetUpUniformCamera();
	void UpdateCamera(const GLfloat* MVP, const GLfloat* V, const GLfloat* M);

	void SetUpUniformLights(int numberOfLights);

	void SetUpUniformLights(std::vector<Light*> objectLights);
	void UpdateLights(std::vector<Light*> objectLight);


};