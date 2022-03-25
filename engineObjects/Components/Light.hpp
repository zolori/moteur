#pragma once
#include "../Component.h"
#include "../../common/Header.h"

class Light : Component {

private:
	vec3 lightPosition;
	vec3 lightColor;
	float lightPower;
	GLuint LightIDPosition;
	GLuint LightIDColor;
	GLuint LightIDPower;

public :
	//Light();
	Light(vec3 newLightPosition, vec3 newLightColor, float newLightPower);
	void SetUniformVar(GLuint programID);
	void SendValueToUniformVar();
	void SendValueToUniformVar(vec3 newLightPosition, vec3 newLightColor, float newLightPower);
	//Getter
	vec3 GetLightPosition();
	vec3 GetLightColor();
	float GetLightPower();
	//Setter
	void SetLightPosition(vec3 newLightPosition);
	void SetLightColor(vec3 newLightColor);
	void SetLightPower(float newLightPower);

	void f();
};
