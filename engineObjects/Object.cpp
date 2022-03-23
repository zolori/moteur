#include "Object.h"
#include <BulletCollision/CollisionDispatch/btCollisionObject.h>

Object::Object(std::string Name, std::string Tag)
{
	name = Name;
	tag = Tag;

	btCollisionObject testObj;
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