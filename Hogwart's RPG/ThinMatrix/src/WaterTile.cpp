#include "pch.h"
#include "WaterTile.h"

float WaterTile::TILE_SIZE = 800.f;

WaterTile::WaterTile(const float & x, const float & z, const float &  height) :
	m_X(x),
	m_Z(z),
	m_Height(height)
{
}

WaterTile::~WaterTile()
{
}
