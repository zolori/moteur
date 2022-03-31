#pragma once
#include "../Component.h"
#include "../../common/Header.h"

class Light : Component {

private:
	const char* name;
	bool active;
	vec3 lightPosition;
	vec3 lightColor;
	float lightPower;

public :
	//Light();
	Light(vec3 newLightPosition, vec3 newLightColor, float newLightPower);
	Light(const char* newName, vec3 newLightPosition, vec3 newLightColor, float newLightPower);

	//Getter
	vec3 GetLightPosition();
	vec3 GetLightColor();
	float GetLightPower();
	const char* GetName();
	bool GetActive();
	//Setter
	void SetActive(bool newActive);
	void SetName(const char* newName);
	void SetLightPosition(vec3 newLightPosition);
	void SetLightColor(vec3 newLightColor);
	void SetLightPower(float newLightPower);

	void f();
};
