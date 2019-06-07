#include "pch.h"
#include "TerrainTexturePack.h"


TerrainTexturePack::TerrainTexturePack(const TerrainTexture & background, const TerrainTexture & RColor, const TerrainTexture & GColor, const TerrainTexture & BColor) :
	m_Background(background),
	m_RColor(RColor),
	m_GColor(GColor),
	m_BColor(BColor)
{
}


TerrainTexturePack::~TerrainTexturePack()
{
}
