#include "pch.h"
#include "OBJLoader.h"

std::vector<float> OBJLoader::positions;
std::vector<float> OBJLoader::texture_coordinates;
std::vector<float> OBJLoader::normals;
std::vector<unsigned int> OBJLoader::indices;

RawModel OBJLoader::LoadModel(const std::string & path, Loader & loader)
{
	positions.clear();
	texture_coordinates.clear();
	normals.clear();
	indices.clear();

	Assimp::Importer importer;
	const aiScene *scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_CalcTangentSpace);

	if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
	{
		std::cerr << "ERROR::ASSIMP::" << importer.GetErrorString() << std::endl;
		return RawModel(0, 0);
	}
	ProcessNode(scene->mRootNode, scene, loader);

	return loader.LoadToVAO(positions, texture_coordinates, normals, indices);
}

void OBJLoader::ProcessNode(aiNode * node, const aiScene * scene, Loader & loader)
{
	for (unsigned int i = 0; i < node->mNumMeshes; ++i)
	{
		aiMesh * mesh = scene->mMeshes[node->mMeshes[i]];
		ProcessMesh(mesh, scene, loader);
	}
	for (unsigned int i = 0; i < node->mNumChildren; ++i)
		ProcessNode(node->mChildren[i], scene, loader);
}

void OBJLoader::ProcessMesh(aiMesh * mesh, const aiScene * scene, Loader & loader)
{
	// Vertices processing
	for (unsigned int i = 0; i < mesh->mNumVertices; ++i)
	{
		// Positions
		positions.push_back(mesh->mVertices[i].x);
		positions.push_back(mesh->mVertices[i].y);
		positions.push_back(mesh->mVertices[i].z);

		// Normals
		if (mesh->mNormals)
		{
			normals.push_back(mesh->mNormals[i].x);
			normals.push_back(mesh->mNormals[i].y);
			normals.push_back(mesh->mNormals[i].z);
		}

		// Texture coordinates
		if (mesh->mTextureCoords[0])
		{
			texture_coordinates.push_back(mesh->mTextureCoords[0][i].x);
			texture_coordinates.push_back(mesh->mTextureCoords[0][i].y);
		}
		else
		{
			texture_coordinates.push_back(0.f);
			texture_coordinates.push_back(0.f);
		}
	}
	// Indices processing
	for (unsigned int i = 0; i < mesh->mNumFaces; ++i)
	{
		aiFace face = mesh->mFaces[i];
		for (unsigned int j = 0; j < face.mNumIndices; ++j)
			indices.push_back(face.mIndices[j]);
	}
}

OBJLoader::OBJLoader() {}

OBJLoader::~OBJLoader() {}