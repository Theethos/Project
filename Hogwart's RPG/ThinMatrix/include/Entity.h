#pragma once

#include "TexturedModel.h"

class Entity
{
public:
	Entity(const TexturedModel & model, const glm::vec3 & position, const glm::vec3 & rotation, const float & scale, const unsigned int & index = 0);
	virtual ~Entity();

	inline const TexturedModel	GetTexturedModel() const { return m_Model; }
	inline const glm::vec3		GetPosition() const { return m_Position; }
	inline const glm::vec3		GetRotation() const { return m_Rotation; }
	inline const float			GetPositionX() const { return m_Position.x; }
	inline const float			GetPositionY() const { return m_Position.y; }
	inline const float			GetPositionZ() const { return m_Position.z; }
	inline const float			GetScale() const { return m_Scale; }

	inline void					SetTexturedModel(const TexturedModel & model) { m_Model = model; }
	inline void					SetPosition(const glm::vec3 & position) { m_Position = position; }
	inline void					SetPositionX(const float & positionX) { m_Position.x = positionX; }
	inline void					SetPositionY(const float & positionY) { m_Position.y = positionY; }
	inline void					SetPositionZ(const float & positionZ) { m_Position.z = positionZ; }
	inline void					SetRotation(const glm::vec3 & rotation) { m_Rotation = rotation; }
	inline void					SetScale(const float & scale) { m_Scale = scale; }

	virtual inline void			IncreasePosition(const float & dx, const float & dy, const float & dz) { m_Position += glm::vec3(dx, dy, dz); }
	virtual inline void			IncreaseRotation(const float & rx, const float & ry, const float & rz) { m_Rotation += glm::vec3(rx, ry, rz); }
	virtual inline float		GetTextureXOffset() const;
	virtual inline float		GetTextureYOffset() const;

protected:
	TexturedModel m_Model;
	glm::vec3 m_Position;
	glm::vec3 m_Rotation;
	float m_Scale;
	unsigned int m_IndexInTextureAtlas;
};

