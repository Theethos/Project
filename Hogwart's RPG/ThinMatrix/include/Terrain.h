#pragma once

#include "Loader.h"
#include "Entity.h"
#include "TerrainTexturePack.h"

class Terrain
{
public:
	Terrain(const int & gridX, const int & gridZ, Loader & loader, const TerrainTexturePack & textures, const TerrainTexture & blendMap);
	Terrain(const Terrain & other);
	Terrain(const Terrain && other);
	~Terrain();

	Terrain & operator=(Terrain & other);
	Terrain & operator=(Terrain && other);

	inline const unsigned int		GetGridX() const { return m_WorldPositionX; }
	inline const unsigned int		GetGridZ() const { return m_WorldPositionZ; }
	inline const RawModel			GetRawModel() const { return m_Model; }
	inline const TerrainTexturePack	GetTextures() const { return m_Textures; }
	inline const TerrainTexture		GetBlendMap() const { return m_BlendMap; }

private:
	static unsigned int Size, VertexCount;
	int m_WorldPositionX, m_WorldPositionZ;
	RawModel m_Model;
	TerrainTexturePack m_Textures;
	TerrainTexture m_BlendMap;

	RawModel GenerateTerrain(Loader & loader);
};

