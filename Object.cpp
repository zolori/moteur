#include "Object.h"

Object::Object(std::string Name, std::string Tag)
{
	name = Name;
	tag = Tag;
}

void Object::RemoveComponent(std::string ComponentName)
{
	for (size_t i = 0; i < components.size(); i++)
	{
		if (components[i]->GetName() == ComponentName)
		{
			components.erase(components.begin() + i);
			return;
		}
	}
}

void Object::Update()
{
}
