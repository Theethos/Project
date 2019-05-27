#pragma once

#include "TexturedModel.h"

class Entity
{
public:
	Entity(const TexturedModel & model, const glm::vec3 & position, const glm::vec3 & rotation, const float & scale);
	~Entity();

	inline const TexturedModel	GetTexturedModel() const { return m_Model; }
	inline const glm::vec3		GetPosition() const { return m_Position; }
	inline const glm::vec3		GetRotation() const { return m_Rotation; }
	inline const float			GetScale() const { return m_Scale; }

	inline void					SetTexturedModel(const TexturedModel & model) { m_Model = model; }
	inline void					SetPosition(const glm::vec3 & position) { m_Position = position; }
	inline void					SetRotation(const glm::vec3 & rotation) { m_Rotation = rotation; }
	inline void					SetScale(const float & scale) { m_Scale = scale; }

	inline void					IncreasePosition(const float & dx, const float & dy, const float & dz) { m_Position += glm::vec3(dx, dy, dz); }
	inline void					IncreaseRotation(const float & rx, const float & ry, const float & rz) { m_Rotation += glm::vec3(rx, ry, rz); }
private:
	TexturedModel m_Model;
	glm::vec3 m_Position;
	glm::vec3 m_Rotation;
	float m_Scale;
};

