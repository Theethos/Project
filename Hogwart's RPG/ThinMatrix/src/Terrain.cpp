#include "pch.h"
#include "Terrain.h"

unsigned int Terrain::Size = 800;
unsigned int Terrain::VertexCount = 128;

Terrain::Terrain(const int & gridX, const int & gridZ, Loader & loader, const TerrainTexturePack & textures, const TerrainTexture & blendMap) :
	m_WorldPositionX(gridX * Size),
	m_WorldPositionZ(gridZ * Size),
	m_Textures(textures),
	m_BlendMap(blendMap),
	m_Model(0, 0)
{
	m_Model = GenerateTerrain(loader);
}

Terrain::Terrain(const Terrain & other) :
	m_WorldPositionX(other.m_WorldPositionX),
	m_WorldPositionZ(other.m_WorldPositionZ),
	m_Model(other.m_Model),
	m_Textures(other.m_Textures),
	m_BlendMap(other.m_BlendMap)
{
}

Terrain::Terrain(const Terrain && other) :
	m_WorldPositionX(other.m_WorldPositionX),
	m_WorldPositionZ(other.m_WorldPositionZ),
	m_Model(other.m_Model),
	m_Textures(other.m_Textures),
	m_BlendMap(other.m_BlendMap)
{
}

Terrain::~Terrain()
{
}

Terrain & Terrain::operator=(Terrain & other)
{
	m_WorldPositionX = other.m_WorldPositionX;
	m_WorldPositionZ = other.m_WorldPositionZ;
	m_Model			 = other.m_Model;
	m_Textures		 = other.m_Textures;
	m_BlendMap		 = other.m_BlendMap;

	return *this;
}

Terrain & Terrain::operator=(Terrain && other)
{
	m_WorldPositionX = other.m_WorldPositionX;
	m_WorldPositionZ = other.m_WorldPositionZ;
	m_Model = other.m_Model;
	m_Textures = other.m_Textures;
	m_BlendMap = other.m_BlendMap;

	return *this;
}

RawModel Terrain::GenerateTerrain(Loader & loader)
{
	std::vector<float> vertices;
	std::vector<float> texture_coordinates;
	std::vector<float> normals;
	std::vector<unsigned int> indices;

	// Vertices
	for (float i = 0.f; i < VertexCount; ++i)
	{
		for (float j = 0.f; j < VertexCount; ++j)
		{
			vertices.push_back(-j / ((float)VertexCount - 1) * Size);
			vertices.push_back(0.f);
			vertices.push_back(-i / ((float)VertexCount - 1) * Size);
			
			texture_coordinates.push_back(j / ((float)VertexCount - 1));
			texture_coordinates.push_back(i / ((float)VertexCount - 1));
			
			normals.push_back(0.f);
			normals.push_back(1.f);
			normals.push_back(0.f);
		}
	}
	// Indices
	for (unsigned int gz = 0; gz < VertexCount - 1; ++gz)
	{
		for (unsigned int gx = 0; gx < VertexCount - 1; ++gx)
		{
			unsigned int top_left = (gz * VertexCount) + gx;
			unsigned int top_right = top_left + 1;
			unsigned int bottom_left = ((gz + 1) * VertexCount) + gx;
			unsigned int bottom_right = bottom_left + 1;
			indices.push_back(top_left);
			indices.push_back(bottom_left);
			indices.push_back(top_right);
			indices.push_back(top_right);
			indices.push_back(bottom_left);
			indices.push_back(bottom_right);
		}
	}

	return loader.LoadToVAO(vertices, texture_coordinates, normals, indices);
}
