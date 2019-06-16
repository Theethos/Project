#pragma once

class WaterTile
{
public:
	WaterTile(const float & x, const float & z, const float &  height);
	~WaterTile();

	inline const float & GetX() const { return m_X; }
	inline const float & GetZ() const { return m_Z; }
	inline const float & GetHeight() const { return m_Height; }

	static float TILE_SIZE;
private:
	float m_X, m_Z, m_Height;
};

