#pragma once

class ModelTexture
{
public:
	ModelTexture(const unsigned & textureID, const float & shininess = 32.f, const float & reflectivity = 1);
	~ModelTexture();

	inline const unsigned int	GetID() const { return m_TextureID; }
	inline const unsigned int	GetNumberOfRows() const { return m_NumberOfRows; }
	inline const float			GetShininess() const { return m_Shininess; }
	inline const float			GetReflectivity() const { return m_Reflectivity; }
	inline const bool			GetTransparency() const { return m_HasTransparency; }
	inline const bool			GetFakeLight() const { return m_HasFakeLight; }

	inline void					SetNumberOfRows(const unsigned int & value) { m_NumberOfRows = value; }
	inline void					SetShininess(const float & shininess) { m_Shininess = shininess; }
	inline void					SetReflectivity(const float & reflectivity) { m_Reflectivity = reflectivity; }
	inline void					SetTransparency(const bool & transparency) { m_HasTransparency = transparency; }
	inline void					SetFakeLight(const bool & useFakeLight) { m_HasFakeLight = useFakeLight; }

private:
	unsigned int m_TextureID, m_NumberOfRows;
	float m_Shininess, m_Reflectivity;
	bool m_HasTransparency, m_HasFakeLight;
};

