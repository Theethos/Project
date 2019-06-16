#include "pch.h"
#include "Entity.h"

Entity::Entity(const TexturedModel & model, const glm::vec3 & position, const glm::vec3 & rotation, const float & scale, const unsigned int & index) :
	m_Model(model),
	m_Position(position),
	m_Rotation(rotation),
	m_Scale(scale),
	m_IndexInTextureAtlas(index)
{
}

Entity::~Entity()
{
}

float Entity::GetTextureXOffset() const
{
	int column = m_IndexInTextureAtlas % m_Model.GetModelTexture().GetNumberOfRows();
	float result = (float)column / (float)m_Model.GetModelTexture().GetNumberOfRows();
	return result;
}

float Entity::GetTextureYOffset() const
{
	int row = m_IndexInTextureAtlas / m_Model.GetModelTexture().GetNumberOfRows();
	float result = (float)row / (float)m_Model.GetModelTexture().GetNumberOfRows();
	return result;
}
