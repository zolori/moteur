#include "Light.hpp"



Light::Light(vec3 newLightPosition, vec3 newLightColor, float newLightPower)
{
	lightPosition = newLightPosition;
	lightColor = newLightColor;
	lightPower = newLightPower;
	active = true;
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
	float curPower=0.0f;
	if (active)
	{
		curPower = lightPower;
	}
	return curPower;
}

const char* Light::GetName()
{
	return name;
}

bool Light::GetActive()
{
	return active;
}

void Light::SetActive(bool newActive)
{
	active = newActive;
}

void Light::SetName(const char* newName)
{
	name = newName;
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