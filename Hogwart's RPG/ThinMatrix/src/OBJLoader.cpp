#include "pch.h"
#include "OBJLoader.h"

enum class ParsingState { NONE, VERTEX, TEXTURE, NORMAL, FACE };
enum class ParsingIndicesState { VERTEX, TEXTURE, NORMAL};
enum class Vertex { X, Y, Z};
enum class Texture { X, Y};
enum class Normal { X, Y, Z};


RawModel OBJLoader::LoadFromFile(const std::string & objPath, Loader & loader)
{
	ParsingState state = ParsingState::NONE;
	ParsingIndicesState pState = ParsingIndicesState::VERTEX;
	Vertex v = Vertex::X; Texture t = Texture::X; Normal n = Normal::X;
	std::ifstream file(objPath);
	std::string line = "";
	std::string vertexIndice = "", textureIndice = "", normalIndice = "";
	std::vector<glm::vec3> positions;
	std::vector<glm::vec2> textureCoords;
	std::vector<glm::vec3> normals;
	float * textureCoordsOrdered = nullptr;
	float * normalsOrdered = nullptr;
	std::vector<unsigned int> indices;
	if (file.is_open())
	{
		while (file >> line)
		{
			if (line[0] == 'v')
			{
				if (line.size() == 1)				// Vertex position
					state = ParsingState::VERTEX;		
				else if (line[1] == 't')			// Texture position 
					state = ParsingState::TEXTURE;
				else if (line[1] == 'n')			// Normal position 
					state = ParsingState::NORMAL;
			}
			else if (line[0] == 'f')				// Face position 
				state = ParsingState::FACE;
			else
			{
				switch (state)
				{
					case ParsingState::VERTEX:
						if (v == Vertex::X)
						{
							positions.push_back(glm::vec3(std::atof(line.c_str()), 0, 0));
							v = Vertex::Y;
						}
						else if (v == Vertex::Y)
						{
							positions.back().y = std::atof(line.c_str());
							v = Vertex::Z;
						}
						else if (v == Vertex::Z)
						{
							positions.back().z = std::atof(line.c_str());
							v = Vertex::X;
						}
						break;
					case ParsingState::TEXTURE:
						std::cout << "texture coord " << line << std::endl;
						if (t == Texture::X)
						{
							textureCoords.push_back(glm::vec2(std::atof(line.c_str()), 0));
							t = Texture::Y;
						}
						else if (t == Texture::Y)
						{
							textureCoords.back().y = std::atof(line.c_str());
							t = Texture::X;
						}
						break;
					case ParsingState::NORMAL:	
						if (n == Normal::X)
						{
							normals.push_back(glm::vec3(std::atof(line.c_str()), 0, 0));
							n = Normal::Y;
						}
						else if (n == Normal::Y)
						{
							normals.back().y = std::atof(line.c_str());
							n = Normal::Z;
						}
						else if (n == Normal::Z)
						{
							normals.back().z = std::atof(line.c_str());
							n = Normal::X;
						}
						break;
					case ParsingState::FACE:
						if (!textureCoordsOrdered && !normalsOrdered)
						{
							textureCoordsOrdered	= new float[positions.size() * 2];
							normalsOrdered			= new float[positions.size() * 3];
						}
						pState = ParsingIndicesState::VERTEX;
						for (unsigned i = 0; i < line.size(); ++i)
						{
							if (line[i] != '/' && line[i] != '\n')
							{
								switch (pState)
								{
									case ParsingIndicesState::VERTEX:	vertexIndice += line[i];	break;
									case ParsingIndicesState::TEXTURE:	textureIndice += line[i];	break;
									case ParsingIndicesState::NORMAL:	normalIndice += line[i];	break;
									default:														break;
								}
							}
							else if (line[i] == '/')
							{
								switch (pState)
								{
									case ParsingIndicesState::VERTEX:	
										indices.push_back((unsigned int)(std::atoi(vertexIndice.c_str()) - 1));
										pState = ParsingIndicesState::TEXTURE;
										break;
									case ParsingIndicesState::TEXTURE:
										textureCoordsOrdered[indices.back() * 2    ] = textureCoords[std::atoi(textureIndice.c_str()) - 1].x;
										textureCoordsOrdered[indices.back() * 2 + 1] = textureCoords[std::atoi(textureIndice.c_str()) - 1].y;
										pState = ParsingIndicesState::NORMAL;
										break;
									default:
										break;
								}
							}
							if (i == line.size() - 1)
							{
								normalsOrdered[indices.back() * 3    ] = normals[std::atoi(normalIndice.c_str()) - 1].x;
								normalsOrdered[indices.back() * 3 + 1] = normals[std::atoi(normalIndice.c_str()) - 1].y;
								normalsOrdered[indices.back() * 3 + 2] = normals[std::atoi(normalIndice.c_str()) - 1].z;
								vertexIndice = ""; textureIndice = ""; normalIndice = "";
								pState = ParsingIndicesState::VERTEX;
							}
						}
						break;
					case ParsingState::NONE:
						break;
					default:				
						break;
				}
			}
		}
		file.close();
		std::vector<float> finalVertices, finalTexCoords, finalNormals;
		for (unsigned j = 0; j < positions.size(); ++j)
		{
			finalVertices.push_back(positions[j].x);
			finalVertices.push_back(positions[j].y);
			finalVertices.push_back(positions[j].z);

			finalTexCoords.push_back(textureCoordsOrdered[j]);
			finalTexCoords.push_back(textureCoordsOrdered[j + 1]);

			finalNormals.push_back(normalsOrdered[j]);
			finalNormals.push_back(normalsOrdered[j + 1]);
			finalNormals.push_back(normalsOrdered[j + 2]);
		}

		return loader.LoadToVAO(finalVertices, indices, finalTexCoords);
	}
	else
	{
		std::cerr << "Can't load the given OBJ file ! Error in file '" << __FILE__ << "', line " << __LINE__ << std::endl;
		return RawModel(0, 0);
	}
}

OBJLoader::OBJLoader()
{
}

OBJLoader::~OBJLoader()
{
}