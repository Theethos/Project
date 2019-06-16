#include "pch.h"
#include "Terrain.h"

float Terrain::SIZE = 800.f;
float Terrain::MAX_HEIGHT = 80.f;
float Terrain::MAX_PIXEL_COLOR = 256 * 256 * 256;

Terrain::Terrain(const int & gridX, const int & gridZ, Loader & loader, const TerrainTexturePack & textures, const TerrainTexture & blendMap, const char * heightMap) :
	m_WorldPositionX(gridX * SIZE),
	m_WorldPositionZ(gridZ * SIZE),
	m_Textures(textures),
	m_BlendMap(blendMap),
	m_Model(0, 0),
	m_VertexCount(0),
	m_MinHeight(200000.f),
	m_Heights(nullptr)
{
	m_Model = GenerateTerrain(loader, heightMap);
}

Terrain::Terrain(const Terrain & other) :
	m_WorldPositionX(other.m_WorldPositionX),
	m_WorldPositionZ(other.m_WorldPositionZ),
	m_Model(other.m_Model),
	m_Textures(other.m_Textures),
	m_BlendMap(other.m_BlendMap),
	m_MinHeight(other.m_MinHeight),
	m_VertexCount(other.m_VertexCount)
{
	m_Heights = new float *[m_VertexCount];
	for (unsigned int i = 0; i < m_VertexCount; ++i)
	{
		m_Heights[i] = new float[m_VertexCount];
		*m_Heights[i] = *other.m_Heights[i];
	}
}

Terrain::Terrain(const Terrain && other) :
	m_WorldPositionX(other.m_WorldPositionX),
	m_WorldPositionZ(other.m_WorldPositionZ),
	m_Model(other.m_Model),
	m_Textures(other.m_Textures),
	m_BlendMap(other.m_BlendMap),
	m_MinHeight(other.m_MinHeight),
	m_VertexCount(other.m_VertexCount)
{
	m_Heights = new float *[m_VertexCount];
	for (unsigned int i = 0; i < m_VertexCount; ++i)
	{
		m_Heights[i] = new float[m_VertexCount];
		*m_Heights[i] = *other.m_Heights[i];
	}
}

Terrain::~Terrain()
{
	if (m_Heights)
	{
		for (unsigned int i = 0; i < m_VertexCount; ++i)
		{
			if (m_Heights[i])
				delete m_Heights[i];
		}
		delete m_Heights;
	}
}

Terrain & Terrain::operator=(Terrain & other)
{
	m_WorldPositionX = other.m_WorldPositionX;
	m_WorldPositionZ = other.m_WorldPositionZ;
	m_Model			 = other.m_Model;
	m_Textures		 = other.m_Textures;
	m_BlendMap		 = other.m_BlendMap;
	m_VertexCount	 = other.m_VertexCount;
	m_MinHeight		 = other.m_MinHeight;
	m_Heights = new float *[m_VertexCount];
	for (unsigned int i = 0; i < m_VertexCount; ++i)
	{
		m_Heights[i] = new float[m_VertexCount];
		*m_Heights[i] = *other.m_Heights[i];
	}

	return *this;
}

Terrain & Terrain::operator=(Terrain && other)
{
	m_WorldPositionX = other.m_WorldPositionX;
	m_WorldPositionZ = other.m_WorldPositionZ;
	m_Model			 = other.m_Model;
	m_Textures		 = other.m_Textures;
	m_BlendMap		 = other.m_BlendMap;
	m_VertexCount	 = other.m_VertexCount;
	m_MinHeight		 = other.m_MinHeight;

	m_Heights = new float *[m_VertexCount];
	for (unsigned int i = 0; i < m_VertexCount; ++i)
	{
		m_Heights[i] = new float[m_VertexCount];
		*m_Heights[i] = *other.m_Heights[i];
	}

	return *this;
}

float Terrain::GetHeightOfTerrain(const float & worldX, const float & worldZ) const
{
	float terrainX = worldX - m_WorldPositionX;
	float terrainZ = worldZ - m_WorldPositionZ;
	float gridSize = SIZE / ((float)m_VertexCount - 1.f);
	int gridX = std::floor(terrainX / gridSize);
	int gridZ = std::floor(terrainZ / gridSize);
	if ((gridX < 0) || (gridX >= m_VertexCount - 1) || (gridZ < 0) || (gridZ >= m_VertexCount - 1))
		return -1000000.f;
	
	float xCoord = fmodf(terrainX, gridSize) / gridSize;
	float zCoord = fmodf(terrainZ, gridSize) / gridSize;

	float result;
	if (xCoord <= (1 - zCoord))
	{
		result = Maths::BarryCentric(glm::vec3(0.f, m_Heights[gridX][gridZ], 0.f),
									 glm::vec3(1.f, m_Heights[gridX + 1][gridZ], 0.f),
									 glm::vec3(0.f, m_Heights[gridX][gridZ + 1], 1.f),
									 glm::vec2(xCoord, zCoord));
	}
	else
	{
		result = Maths::BarryCentric(glm::vec3(1.f, m_Heights[gridX + 1][gridZ], 0.f),
									 glm::vec3(1.f, m_Heights[gridX + 1][gridZ + 1], 1.f),
									 glm::vec3(0.f, m_Heights[gridX][gridZ + 1], 1.f),
									 glm::vec2(xCoord, zCoord));
	}
	return result;
}

RawModel Terrain::GenerateTerrain(Loader & loader, const char * heightMap)
{
	SDL_Surface * data = IMG_Load(heightMap);
	if(!data)
	{
		std::cerr << "Failed to load the heightMap\n";
	}
	m_VertexCount = data->w;

	std::vector<float> vertices;
	std::vector<float> texture_coordinates;
	std::vector<float> normals;
	std::vector<unsigned int> indices;

	m_Heights = new float * [m_VertexCount];
	for (unsigned int i = 0; i < m_VertexCount; ++i)
		m_Heights[i] = new float[m_VertexCount];

	// Vertices
	for (float i = 0.f; i < m_VertexCount; ++i)
	{
		for (float j = 0.f; j < m_VertexCount; ++j)
		{
			vertices.push_back(j / ((float)m_VertexCount - 1) * SIZE);
			if (data)
				m_Heights[(unsigned int)j][(unsigned int)i] = GetHeight(j, i, data);
			else
				m_Heights[(unsigned int)j][(unsigned int)i] = 0.f;
			vertices.push_back(m_Heights[(unsigned int)j][(unsigned int)i]);
			vertices.push_back(i / ((float)m_VertexCount - 1) * SIZE);
			
			texture_coordinates.push_back(j / ((float)m_VertexCount - 1));
			texture_coordinates.push_back(i / ((float)m_VertexCount - 1));
			
			glm::vec3 normal = CalculateNormal(j, i, data);
			normals.push_back(normal.x);
			normals.push_back(normal.y);
			normals.push_back(normal.z);
		}
	}
	// Indices
	for (unsigned int gz = 0; gz < m_VertexCount - 1; ++gz)
	{
		for (unsigned int gx = 0; gx < m_VertexCount - 1; ++gx)
		{
			unsigned int top_left = (gz * m_VertexCount) + gx;
			unsigned int top_right = top_left + 1;
			unsigned int bottom_left = ((gz + 1) * m_VertexCount) + gx;
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

inline float Terrain::GetHeight(const unsigned int & x, const unsigned int & y, const SDL_Surface * data)
{
	if (x < 0 || x >= data->w || y < 0 || y >= data->h)
		return 0.f;
	Uint32 pixel = (((Uint32 *)data->pixels)[x * data->pitch / 4 + y]);
	Uint8 r, g, b;
	SDL_GetRGB(pixel, data->format, &r, &g, &b);
	float height = r * g * b;
	height += (MAX_PIXEL_COLOR / 2.f);
	height /= (MAX_PIXEL_COLOR / 2.f);
	height *= MAX_HEIGHT;
	if (height < m_MinHeight)
		m_MinHeight = height;
	return height;

	//return ((float)(r * g * b) - (MAX_PIXEL_COLOR / 2.f)) / (MAX_PIXEL_COLOR / 2.f) * MAX_HEIGHT;
}

glm::vec3 Terrain::CalculateNormal(const unsigned int & x, const unsigned int & y, const SDL_Surface * data)
{
	float heightL = GetHeight(x - 1, y, data);
	float heightR = GetHeight(x + 1, y, data);
	float heightD = GetHeight(x, y - 1, data);
	float heightU = GetHeight(x, y + 1, data);
	return glm::normalize(glm::vec3(heightL - heightR, 2.f, heightD - heightU));
}

