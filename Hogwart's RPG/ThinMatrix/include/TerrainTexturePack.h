#pragma once

#include "TerrainTexture.h"

class TerrainTexturePack
{
public:
	TerrainTexturePack(const TerrainTexture & background, const TerrainTexture & RColor, const TerrainTexture & GColor, const TerrainTexture & BColor);
	~TerrainTexturePack();

	inline const TerrainTexture & GetBackground() const { return m_Background; }
	inline const TerrainTexture & GetRColor() const { return m_RColor; }
	inline const TerrainTexture & GetGColor() const { return m_GColor; }
	inline const TerrainTexture & GetBColor() const { return m_BColor; }

private:
	TerrainTexture m_Background, m_RColor, m_GColor, m_BColor;
};

