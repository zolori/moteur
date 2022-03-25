#include "Light.hpp"



Light::Light(vec3 newLightPosition, vec3 newLightColor, float newLightPower)
{
	lightPosition = newLightPosition;
	lightColor = newLightColor;
	lightPower = newLightPower;
}

void Light::SetUniformVar(GLuint programID)
{
	LightIDPosition = glGetUniformLocation(programID, "LightPosition_worldspace");
	LightIDColor = glGetUniformLocation(programID, "LightParam_Color");
	LightIDPower = glGetUniformLocation(programID, "LightParam_Power");
}

void Light::SendValueToUniformVar()
{
	glUniform3f(LightIDPosition, lightPosition.x, lightPosition.y, lightPosition.z);
	glUniform3f(LightIDColor, lightColor.x, lightColor.y, lightColor.z);
	glUniform1f(LightIDPower, lightPower);
}

void Light::SendValueToUniformVar(vec3 newLightPosition, vec3 newLightColor, float newLightPower)
{
	glUniform3f(LightIDPosition, newLightPosition.x, newLightPosition.y, newLightPosition.z);
	glUniform3f(LightIDColor, newLightColor.x, newLightColor.y, newLightColor.z);
	glUniform1f(LightIDPower, newLightPower);
}

vec3 Light::GetLightPosition()
{
	return lightPosition;
}

vec3 Light::GetLightColor()
{
	return lightColor;
}

float Light::GetLightPower()
{
	return lightPower;
}

void Light::SetLightPosition(vec3 newLightPosition)
{
	lightPosition = newLightPosition;

}

void Light::SetLightColor(vec3 newLightColor)
{
	lightColor = newLightColor;
}

void Light::SetLightPower(float newLightPower)
{
	lightPower = newLightPower;
}

void Light::f()
{

}