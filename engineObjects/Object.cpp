#include "Object.h"

Object::Object(std::string Name)
{
	name = Name;
}

Component* Object::GetSpecificComponent(ComponentName ComponentName)
{
	for (size_t i = 0; i < components.size(); i++)
	{
		if (components[i]->name == ComponentName)
		{
			return components[i];
		}
	}
}

void Object::RemoveComponent(ComponentName ComponentName)
{
	for (size_t i = 0; i < components.size(); i++)
	{
		if (components[i]->name == ComponentName)
		{
			components.erase(components.begin() + i);
			return;
		}
	}
}