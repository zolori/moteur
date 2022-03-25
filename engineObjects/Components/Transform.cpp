#include "Transform.h"

Transform::Transform(glm::vec3 Position, glm::vec3 Rotation, glm::vec3 Scale)
{
	position = Position;
	rotation = Rotation;
	scale = Scale;
	name = ComponentName::TRANSFORM_COMPONENT;
}
