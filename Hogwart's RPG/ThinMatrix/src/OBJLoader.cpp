#include "pch.h"
#include "OBJLoader.h"

enum class ParsingState { NONE, VERTEX, TEXTURE, NORMAL, FACE };
enum class ParsingIndicesState { VERTEX, TEXTURE, NORMAL };
enum class Vertex { X, Y, Z };
enum class Texture { X, Y };
enum class Normal { X, Y, Z };


RawModel OBJLoader::LoadFromFile(const std::string & objPath, Loader & loader)
{
	// State defining what to do when there is "v ", "vt", "vn", and "t " on the beginning of a line
	ParsingState state = ParsingState::NONE;									// None is for the first line
	// State defining the type of data when we reach "f v/t/n v/t/n v/t/v" (faces lines)
	ParsingIndicesState pState = ParsingIndicesState::VERTEX;
	// Enum defining to what coordinate of the vector the data should be added
	Vertex v = Vertex::X; Texture t = Texture::X; Normal n = Normal::X;
	std::ifstream file(objPath);
	std::string line = "", index = "";											// index = value of index when we have v/t/n
	// Vectors containing the data
	std::vector<glm::vec3> vertices, normals;
	std::vector<glm::vec2> textures_coordinates;
	std::vector<unsigned int> indices;
	// Table that contains ordered data (because they are not ordered by default)
	float * ordered_textures = nullptr, * ordered_normals = nullptr;

	if (file.is_open())
	{
		while (file >> line)
		{
			// Switching state depending on how the line begins
			if (line[0] == 'v')
			{
				if (line.size() == 1)				// Vertex coordinates
					state = ParsingState::VERTEX;		
				else if (line[1] == 't')			// Texture coordinates 
					state = ParsingState::TEXTURE;
				else if (line[1] == 'n')			// Normal coordinates 
					state = ParsingState::NORMAL;
			}
			else if (line[0] == 'f')				// Faces
				state = ParsingState::FACE;
			else
			{
				switch (state)
				{
					// Then if it is a line containing vertex coordinates
					// (v x.xxxxx y.yyyyy z.zzzzz)
					case ParsingState::VERTEX:
						if (v == Vertex::X)
						{
							// The first coordinate is the X one
							vertices.push_back(glm::vec3(std::atof(line.c_str()), 0, 0));
							v = Vertex::Y;
						}
						else if (v == Vertex::Y)
						{
							// Then the Y one
							vertices.back().y = std::atof(line.c_str());
							v = Vertex::Z;
						}
						else if (v == Vertex::Z)
						{
							// And finally the Z one
							vertices.back().z = std::atof(line.c_str());
							v = Vertex::X;
						}
						break;
					// Same for textures and normals
					//vt x.xxxxx y.yyyyy
					case ParsingState::TEXTURE:
						if (t == Texture::X)
						{
							textures_coordinates.push_back(glm::vec2(std::atof(line.c_str()), 0));
							t = Texture::Y;
						}
						else if (t == Texture::Y)
						{
							textures_coordinates.back().y = std::atof(line.c_str());
							t = Texture::X;
						}
						break;
					//vn x.xxxxx y.yyyyy z.zzzzz
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
					//f v/t/n v/t/n v/t/n
					case ParsingState::FACE:
						/*	Here we have to order the textures coordinates and the normals depending on their associated
							vertex indice, so we create to table, and we can give them a size now that we have all the 
							vertices coordinates																		  */
						if (!ordered_textures && !ordered_normals)
						{
							// There are two textures coordinates and three normals / vertices (glm::vec3 for now)
							ordered_textures	= new float[vertices.size() * 2];
							ordered_normals		= new float[vertices.size() * 3];
						}
						pState = ParsingIndicesState::VERTEX;
						for (unsigned i = 0; i < line.size(); ++i)
						{
							// Then we parse the line, which is like "v/t/n"
							if (line[i] != '/')
							{
								index += line[i];
							}
							else if (line[i] == '/')
							{
								switch (pState)
								{
									// First we push the indice
									case ParsingIndicesState::VERTEX:	
										//std::cout << line << " " << index << " ";
										indices.push_back((unsigned int)(std::atoi(index.c_str()) - 1));
										index = "";
										pState = ParsingIndicesState::TEXTURE;
										break;
									// Then the texture coordinates in the right index in the ordered table
									case ParsingIndicesState::TEXTURE:
										//std::cout << index << " ";
										ordered_textures[indices.back() * 2    ] = textures_coordinates[std::atoi(index.c_str()) - 1].x;
										ordered_textures[indices.back() * 2 + 1] = textures_coordinates[std::atoi(index.c_str()) - 1].y;
										index = "";
										pState = ParsingIndicesState::NORMAL;
										break;
									default:
										break;
								}
								
							}
							// And then the same for the normals
							if (i == line.size() - 1)
							{
								//std::cout << index << "\n";
								ordered_normals[indices.back() * 3    ] = normals[std::atoi(index.c_str()) - 1].x;
								ordered_normals[indices.back() * 3 + 1] = normals[std::atoi(index.c_str()) - 1].y;
								ordered_normals[indices.back() * 3 + 2] = normals[std::atoi(index.c_str()) - 1].z;
								index = "";
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
		/*	In the end, we have to convert the ordered table into vertor<float> and the vertices into vector<float>
			instead of vector<vec3>																					 */
		std::vector<float> final_vertices, final_textures_coordinates, final_normals;
		for (unsigned j = 0; j < vertices.size(); ++j)
		{
			final_vertices.push_back(vertices[j].x);
			final_vertices.push_back(vertices[j].y);
			final_vertices.push_back(vertices[j].z);

			final_textures_coordinates.push_back(ordered_textures[j	   ]);
			final_textures_coordinates.push_back(ordered_textures[j + 1]);

			final_normals.push_back(ordered_normals[j	]);
			final_normals.push_back(ordered_normals[j + 1]);
			final_normals.push_back(ordered_normals[j + 2]);
		}
		// Finally, we can load all the data in a vao and create a row model
		return loader.LoadToVAO(final_vertices, final_textures_coordinates, final_normals, indices);
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