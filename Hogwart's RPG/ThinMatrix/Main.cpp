////////////////////////////////////////////////////////////////////////////////////////
/// Application made with the purpose of learning OpenGL through the tutorial of 
/// ThinMatrix on YouTube. This project is an adaptation of the code originally made in
/// Java. You can find his tutorial following this link :
/// https://www.youtube.com/watch?v=VS8wlS9hF8E&list=PLRIWtICgwaX0u7Rf9zkZhLoLuZVfUksDP
////////////////////////////////////////////////////////////////////////////////////////
#include "pch.h"
#include "Renderer.h"	// "TexturedModel.h"
#include "Loader.h"
#include "Shader.h"
#include "Camera.h"
#include "OBJLoader.h"
#include "Player.h"
#undef main // SDL macro to create a main function
////////////////////////////////////////////////////////////////////////////////////////
/// \brief Entry point of the application
/// \return Application exit code 
////////////////////////////////////////////////////////////////////////////////////////

#define BOUNDS(left, right, value) std::min(std::max(left, value), right)

static void ProcessEntities(std::map<TexturedModel, std::vector<Entity *>> & entities, std::vector<Entity *> & entitiesToProcess)
{
	const TexturedModel & texModel = entitiesToProcess[0]->GetTexturedModel();
	if (entities[texModel].size())
	{
		std::vector<Entity *> & vector = entities[texModel];
		vector.insert(vector.end(), entitiesToProcess.begin(), entitiesToProcess.end());
	}
	else
	{
		entities[texModel] = entitiesToProcess;
	}
}

static void ProcessEntity(std::map<TexturedModel, std::vector<Entity *>> & entities, Entity * entityToProcess)
{
	const TexturedModel & texModel = entityToProcess->GetTexturedModel();
	entities[texModel].push_back(entityToProcess);
}

int main(int argc, char * argv[])
{
	DisplayManager::Create(800, 600, false);
	InputManager::Create();

	Loader loader;
	Shader staticShader("StaticShader");
	Shader terrainShader("TerrainShader");
	Renderer renderer;

	std::vector<float> positions = {
	-0.5f, -0.5f, -0.5f,
	 0.5f, -0.5f, -0.5f,
	 0.5f,  0.5f, -0.5f,
	-0.5f,  0.5f, -0.5f,

	-0.5f, -0.5f,  0.5f,
	 0.5f, -0.5f,  0.5f,
	 0.5f,  0.5f,  0.5f,
	-0.5f,  0.5f,  0.5f,

	-0.5f,  0.5f,  0.5f,
	-0.5f,  0.5f, -0.5f,
	-0.5f, -0.5f, -0.5f,
	-0.5f, -0.5f,  0.5f,

	 0.5f,  0.5f,  0.5f,
	 0.5f,  0.5f, -0.5f,
	 0.5f, -0.5f, -0.5f,
	 0.5f, -0.5f,  0.5f,

	-0.5f, -0.5f, -0.5f,
	 0.5f, -0.5f, -0.5f,
	 0.5f, -0.5f,  0.5f,
	-0.5f, -0.5f,  0.5f,

	-0.5f,  0.5f, -0.5f,
	 0.5f,  0.5f, -0.5f,
	 0.5f,  0.5f,  0.5f,
	-0.5f,  0.5f,  0.5f,
	};
	std::vector<float> textureCoords = {
			1,0,
			0,0,
			0,1,
			1,1,
			
			0,0,
			0,1,
			1,1,
			1,0,
			
			0,0,
			0,1,
			1,1,
			1,0,
			
			0,0,
			0,1,
			1,1,
			1,0,
			
			0,0,
			0,1,
			1,1,
			1,0,
			
			0,0,
			0,1,
			1,1,
			1,0
	};
	std::vector<float> normals{
		  0.0f,  0.0f, -1.0f,
		  0.0f,  0.0f, -1.0f,
		  0.0f,  0.0f, -1.0f,
		  0.0f,  0.0f, -1.0f,

		  0.0f,  0.0f, 1.0f,
		  0.0f,  0.0f, 1.0f,
		  0.0f,  0.0f, 1.0f,
		  0.0f,  0.0f, 1.0f,

		 -1.0f,  0.0f,  0.0f,
		 -1.0f,  0.0f,  0.0f,
		 -1.0f,  0.0f,  0.0f,
		 -1.0f,  0.0f,  0.0f,

		  1.0f,  0.0f,  0.0f,
		  1.0f,  0.0f,  0.0f,
		  1.0f,  0.0f,  0.0f,
		  1.0f,  0.0f,  0.0f,

		  0.0f, -1.0f,  0.0f,
		  0.0f, -1.0f,  0.0f,
		  0.0f, -1.0f,  0.0f,
		  0.0f, -1.0f,  0.0f,

		  0.0f,  1.0f,  0.0f,
		  0.0f,  1.0f,  0.0f,
		  0.0f,  1.0f,  0.0f,
		  0.0f,  1.0f,  0.0f,
	};
	std::vector<unsigned int> indices = {
			0,1,2,
			0,3,2,
			
			4,5,6,
			4,7,6,
			
			8,9,10,
			8,11,10,
			
			12,13,14,
			12,15,14,
			
			16,17,18,
			16,19,18,
			
			20,21,22,
			20,23,22
	};

	RawModel model = OBJLoader::LoadModel("res/models/dragon.obj", loader);
	RawModel fernModel = OBJLoader::LoadModel("res/models/Fern.obj", loader);
	RawModel cubeModel = loader.LoadToVAO(positions, textureCoords, normals, indices);
	RawModel lowPolyTreeModel = OBJLoader::LoadModel("res/models/Low_Poly.obj", loader);
	RawModel grassModel = OBJLoader::LoadModel("res/models/Grass.obj", loader);
	RawModel flowerModel = OBJLoader::LoadModel("res/models/Grass.obj", loader);
	RawModel treeModel = OBJLoader::LoadModel("res/models/tree.obj", loader);
	RawModel playerModel = OBJLoader::LoadModel("res/models/player.obj", loader);

	ModelTexture whiteTexture(loader.LoadTexture("res/models/white.png"));
	whiteTexture.SetTransparency(true);
	ModelTexture lowTreeTexture(loader.LoadTexture("res/models/Low_Poly.png"));
	ModelTexture treeTexture(loader.LoadTexture("res/models/tree.png"));
	ModelTexture grassTexture(loader.LoadTexture("res/models/Grass.png"));
	grassTexture.SetTransparency(true);
	grassTexture.SetFakeLight(true);
	ModelTexture fernTexture(loader.LoadTexture("res/models/Fern.png"));
	fernTexture.SetTransparency(true);
	ModelTexture flowerTexture(loader.LoadTexture("res/textures/flowers/flower000.png"));
	flowerTexture.SetTransparency(true);
	flowerTexture.SetFakeLight(true);
	ModelTexture playerTexture(loader.LoadTexture("res/models/player.png"));

	TexturedModel texPlayer(playerModel, playerTexture);
	TexturedModel texLowTree(lowPolyTreeModel, lowTreeTexture);
	TexturedModel texGrass(grassModel, grassTexture);
	TexturedModel texFern(fernModel, fernTexture);
	TexturedModel texFlower(flowerModel, flowerTexture);
	TexturedModel texTree(treeModel, treeTexture);

	Light light(glm::vec3(20000, 40000, 20000), glm::vec3(1, 1, 1));

	std::map<TexturedModel, std::vector<Entity *>> entities;
	for (unsigned int i = 0; i < 250; ++i)
	{
		ProcessEntity(entities, new Entity(texFern, { ((float)(rand() % 100) / 100.f ) * 800.f - 800.f, 0.f, ((float)(rand() % 100) / 100.f ) * - 800.f }, { 0, 0, 0 }, 0.6f));
		ProcessEntity(entities, new Entity(texLowTree, { ((float)(rand() % 100) / 100.f )  * 800.f - 800.f, 0.f, ((float)(rand() % 100) / 100.f ) * - 800.f }, { 0, 0, 0 }, 5.f));
		ProcessEntity(entities, new Entity(texTree, { ((float)(rand() % 100) / 100.f )  * 800.f - 800.f, 0.f, ((float)(rand() % 100) / 100.f ) * - 800.f }, { 0, 0, 0 }, 5.f));
		ProcessEntity(entities, new Entity(texGrass, { ((float)(rand() % 100) / 100.f ) * 800.f - 800.f, 0.f, ((float)(rand() % 100) / 100.f ) * - 800.f }, { 0, 0, 0 }, 1.8f));
		ProcessEntity(entities, new Entity(texFlower, { ((float)(rand() % 100) / 100.f ) * 800.f - 800.f, 0.f, ((float)(rand() % 100) / 100.f ) * - 800.f }, { 0, 0, 0 }, 2.3f));
	}
	
	/*** TERRAIN TEXTURES ***/
	TerrainTexturePack terrainTexPack({ loader.LoadTexture("res/textures/vegetal/veg000.png") }, { loader.LoadTexture("res/textures/ground/ground000.png") },
									  { loader.LoadTexture("res/textures/vegetal/veg070.png") }, { loader.LoadTexture("res/textures/rock-stone/rock000.png") });
	TerrainTexture blendMap = loader.LoadTexture("res/blendmaps/blendmap_0.png");

	std::vector<Terrain> terrains
	{
		Terrain(0, 0, loader, terrainTexPack, blendMap)
	};

	// Player
	Player player(texPlayer, { -200, 0, -200 }, { 0, 0, 0 }, 0.5f);
	ProcessEntity(entities, &player);

	Camera camera(player);


	while (DisplayManager::ShouldBeRunning())
	{
		DisplayManager::StartLoop();

		camera.Move(DisplayManager::GetDeltaTime());
		player.Move(DisplayManager::GetDeltaTime());

		renderer.RenderTerrains(terrains, terrainShader, light, camera);
		//renderer.RenderEntity(player, staticShader, light, camera);
		renderer.RenderEntities(entities, staticShader, light, camera);
		//renderer.RenderEntity(entity, staticShader, light, camera);

		DisplayManager::EndLoop();
	}

	DisplayManager::Destroy();
	InputManager::Destroy();
	//system("pause");
	return 0;
}