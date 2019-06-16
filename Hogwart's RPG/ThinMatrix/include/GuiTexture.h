#pragma once

class GuiTexture
{
public:
	GuiTexture(const glm::vec2 & position, const glm::vec2 & scale, const unsigned int & textureID);
	~GuiTexture();

	inline glm::vec2	GetPosition() const { return m_Position; }
	inline glm::vec2	GetScale() const { return m_Scale; }
	inline unsigned int GetTexture() const { return m_Texture; }

private:
	unsigned int m_Texture;
	glm::vec2 m_Position, m_Scale;
};

