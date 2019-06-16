#pragma once

#include "Loader.h"
#include "Entity.h"
#include "TerrainTexturePack.h"

class Terrain
{
public:
	Terrain(const int & gridX, const int & gridZ, Loader & loader, const TerrainTexturePack & textures, const TerrainTexture & blendMap, const char * heightMap);
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
	inline const float				GetMinimumHeight() const { return m_MinHeight; }
	float							GetHeightOfTerrain(const float & worldX, const float & worldZ) const;

private:
	static float SIZE, MAX_HEIGHT, MAX_PIXEL_COLOR;
	int m_WorldPositionX, m_WorldPositionZ, m_VertexCount;
	RawModel m_Model;
	TerrainTexturePack m_Textures;
	TerrainTexture m_BlendMap;
	float ** m_Heights, m_MinHeight;
	RawModel		GenerateTerrain(Loader & loader, const char * heightMap);
	inline float	GetHeight(const unsigned int & x, const unsigned int & y, const SDL_Surface * data);
	glm::vec3		CalculateNormal(const unsigned int & x, const unsigned int & y, const SDL_Surface * data);
};

