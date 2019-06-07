#pragma once

#include "Loader.h"

class OBJLoader
{
public:
	static RawModel LoadModel(const std::string & path, Loader & loader);

private:
	OBJLoader();
	~OBJLoader();

	static std::vector<float> positions;
	static std::vector<float> texture_coordinates;
	static std::vector<float> normals;
	static std::vector<unsigned int> indices;

	static void ProcessNode(aiNode * node, const aiScene * scene, Loader & loader);
	static void ProcessMesh(aiMesh * mesh, const aiScene * scene, Loader & loader);
};

