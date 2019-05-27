#include "pch.h"
#include "Entity.h"

Entity::Entity(const TexturedModel & model, const glm::vec3 & position, const glm::vec3 & rotation, const float & scale) :
	m_Model(model),
	m_Position(position),
	m_Rotation(rotation),
	m_Scale(scale)
{
}

Entity::~Entity()
{
}
