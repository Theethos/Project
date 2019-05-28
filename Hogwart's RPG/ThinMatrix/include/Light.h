#pragma once

class Light
{
public:
	Light(const glm::vec3 & position, const glm::vec3 & color);
	~Light();

	inline const glm::vec3	GetPosition() const { return m_Position; }
	inline const glm::vec3	GetColor() const { return m_Color; }
	inline void				SetPosition(const glm::vec3 & position) { m_Position = position; }
	inline void				SetColor(const glm::vec3 & color) { m_Color = color; }

private:
	glm::vec3 m_Position, m_Color;
};

