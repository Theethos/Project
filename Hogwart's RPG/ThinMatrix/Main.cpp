////////////////////////////////////////////////////////////////////////////////////////
/// Application made with the purpose of learning OpenGL through the tutorial of 
/// ThinMatrix on YouTube. This project is an adaptation of the code originally made in
/// Java. You can find his tutorial following this link :
/// https://www.youtube.com/watch?v=VS8wlS9hF8E&list=PLRIWtICgwaX0u7Rf9zkZhLoLuZVfUksDP
////////////////////////////////////////////////////////////////////////////////////////
#include "pch.h"
#include "Renderer.h"	// "TexturedModel.h"
#include "Loader.h"
#include "Camera.h"
#include "OBJLoader.h"
#include "Player.h"
#include "GuiRenderer.h"	// Shader.h
#include "SkyboxRenderer.h"
#include "WaterRenderer.h"
#include "WaterFrameBuffer.h"
#undef main // SDL macro to create a main function
////////////////////////////////////////////////////////////////////////////////////////
/// \brief Entry point of the application
/// \return Application exit code 
////////////////////////////////////////////////////////////////////////////////////////

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
	srand(time(NULL));

	DisplayManager::Create();
	DisplayManager::Create(800, 600, false);
	InputManager::Create();

	Loader loader;
	Shader staticShader("StaticShader");
	Shader terrainShader("TerrainShader");
	Renderer renderer;
	GuiRenderer guiRenderer(loader);
	SkyboxRenderer skyboxRenderer(loader);

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
	RawModel treeModel = OBJLoader::LoadModel("res/models/pine.obj", loader);
	RawModel playerModel = OBJLoader::LoadModel("res/models/player.obj", loader);
	RawModel lampModel = OBJLoader::LoadModel("res/models/lamp.obj", loader);

	ModelTexture whiteTexture(loader.LoadTexture("res/models/white.png"));
	whiteTexture.SetTransparency(true);
	ModelTexture lowTreeTexture(loader.LoadTexture("res/models/Low_Poly.png"));
	ModelTexture treeTexture(loader.LoadTexture("res/models/pine.png"));
	treeTexture.SetShininess(256.f);
	treeTexture.SetReflectivity(0.1f);
	ModelTexture grassTexture(loader.LoadTexture("res/models/Grass.png"));
	grassTexture.SetTransparency(true);
	grassTexture.SetFakeLight(true);
	ModelTexture fernTexture(loader.LoadTexture("res/models/fern_atlas.png"), 32.f, 0);
	fernTexture.SetNumberOfRows(2);
	fernTexture.SetTransparency(true);
	ModelTexture flowerTexture(loader.LoadTexture("res/textures/flowers/flower000.png"));
	flowerTexture.SetTransparency(true);
	flowerTexture.SetFakeLight(true);
	ModelTexture playerTexture(loader.LoadTexture("res/models/player.png"));
	ModelTexture lampTexture(loader.LoadTexture("res/models/lamp.png"));

	TexturedModel texCube(cubeModel, whiteTexture);
	TexturedModel texPlayer(playerModel, playerTexture);
	TexturedModel texLowTree(lowPolyTreeModel, lowTreeTexture);
	TexturedModel texGrass(grassModel, grassTexture);
	TexturedModel texFern(fernModel, fernTexture);
	TexturedModel texFlower(flowerModel, flowerTexture);
	TexturedModel texTree(treeModel, treeTexture);
	TexturedModel texLamp(lampModel, lampTexture);

	std::map<TexturedModel, std::vector<Entity *>> entities;

	/*** TERRAIN TEXTURES ***/
	TerrainTexturePack terrainTexPack({ loader.LoadTexture("res/textures/vegetal/veg000.png") }, { loader.LoadTexture("res/textures/ground/ground000.png") },
									  { loader.LoadTexture("res/textures/vegetal/veg070.png") }, { loader.LoadTexture("res/textures/rock-stone/rock000.png") });
	TerrainTexture blendMap = loader.LoadTexture("res/blendmaps/blendmap_0.png");

	Terrain terrain(0, 0, loader, terrainTexPack, blendMap, "res/heightmaps/heightmap_0.png");
	std::vector<Terrain> terrains;
	terrains.push_back(terrain);

	WaterFrameBuffer waterBuffers;
	WaterRenderer waterRenderer(loader, waterBuffers);
	std::vector<WaterTile> waters
	{
		WaterTile(WaterTile::TILE_SIZE, WaterTile::TILE_SIZE , terrain.GetMinimumHeight() + 10.f)
	};


	float x, y, z;
	for (unsigned int i = 0; i < 250; ++i)
	{
		x = ((float)(rand() % 100) / 100.f) * 800.f;
		z = ((float)(rand() % 100) / 100.f) * 800.f;
		y = terrain.GetHeightOfTerrain(x, z);
		while (y < waters[0].GetHeight())
		{
			x = ((float)(rand() % 100) / 100.f) * 800.f;
			z = ((float)(rand() % 100) / 100.f) * 800.f;
			y = terrain.GetHeightOfTerrain(x, z);
		}
		ProcessEntity(entities, new Entity(texFern, { x, y, z}, { 0, 0, 0 }, 0.6f, rand() % 4));
		x = ((float)(rand() % 100) / 100.f) * 800.f;
		z = ((float)(rand() % 100) / 100.f) * 800.f;
		y = terrain.GetHeightOfTerrain(x, z);
		while (y < waters[0].GetHeight())
		{
			x = ((float)(rand() % 100) / 100.f) * 800.f;
			z = ((float)(rand() % 100) / 100.f) * 800.f;
			y = terrain.GetHeightOfTerrain(x, z);
		}
		ProcessEntity(entities, new Entity(texTree, { x, y, z}, { 0, 0, 0 }, std::fmodf((float)rand(), 2.f)));
	}
	
	// Player
	Player player(texPlayer, { 185.f, terrain.GetHeightOfTerrain(185.f, 200.f), 200.f }, { 0, 0, 0 }, 0.5f);

	std::vector<Light> lights
	{
		Light(glm::vec3(- 20000, 40000, - 20000), glm::vec3(1, 1, 1)),
		//Light(glm::vec3(185, terrain.GetHeightOfTerrain(185.f,200.f) + 12, 200), glm::vec3(10, 0, 0), glm::vec3(1, 0.01f, 0.002f)),
		//Light(glm::vec3(370, terrain.GetHeightOfTerrain(370.f,300.f) + 12, 300), glm::vec3(0, 0, 10), glm::vec3(1, 0.01f, 0.002f)),
		//Light(glm::vec3(293, terrain.GetHeightOfTerrain(293.f,305.f) + 12, 305), glm::vec3(0, 10, 0), glm::vec3(1, 0.01f, 0.002f)),
	};

	/*for (unsigned int i = 0; i < lights.size(); ++i)
	{
		auto light_pos = lights[i].GetPosition();
		ProcessEntity(entities, new Entity(texLamp, { light_pos.x, terrain.GetHeightOfTerrain(light_pos.x, light_pos.z), light_pos.z }, { 0, 0, 0 }, 1.f));
		ProcessEntity(entities, new Entity(texCube, light_pos, { 0, 0, 0 }, 1.f));
	}*/

	Camera camera(player);

	InputManager::HideCursor(true);
	InputManager::CatchCursor(true);

	while (DisplayManager::ShouldBeRunning())
	{
		DisplayManager::StartLoop();

		lights[0].SetColor(DisplayManager::GetFogColor() + glm::vec4(0.1, 0.1, 0.1, 1.0));
		auto rotation = glm::radians(skyboxRenderer.GetRotation());
		lights[0].SetPosition({ -20000 * sin(rotation), 40000, -20000 * cos(rotation) });

		player.Move(terrain, DisplayManager::GetFrameTime());
		camera.Move(terrain, DisplayManager::GetFrameTime());

		glEnable(GL_CLIP_DISTANCE0);
		waterBuffers.BindReflectionFrameBuffer();
		float distance = 2 * (camera.GetPosition().y - waters[0].GetHeight());
		camera.GetPosition().y -= distance;
		camera.InvertPitch();
		renderer.RenderTerrains(terrains, terrainShader, lights, camera, { 0, 1, 0, -waters[0].GetHeight() });
		renderer.RenderEntities(entities, staticShader, lights, camera, { 0, 1, 0, -waters[0].GetHeight() });
		if (camera.GetState() != CameraStates::FP)
			renderer.RenderEntity(&player, staticShader, lights, camera, { 0, 1, 0, -waters[0].GetHeight() });
		glDisable(GL_CLIP_DISTANCE0);
		skyboxRenderer.RenderSkybox(camera);
		camera.GetPosition().y += distance;
		camera.InvertPitch();

		glEnable(GL_CLIP_DISTANCE0);
		waterBuffers.BindRefractionFrameBuffer();
		renderer.RenderTerrains(terrains, terrainShader, lights, camera, { 0, -1, 0, waters[0].GetHeight() + 1});
		renderer.RenderEntities(entities, staticShader, lights, camera, { 0, -1, 0, waters[0].GetHeight() + 1 });
		if (camera.GetState() != CameraStates::FP)
			renderer.RenderEntity(&player, staticShader, lights, camera, { 0, -1, 0, waters[0].GetHeight() + 1 });
		glDisable(GL_CLIP_DISTANCE0);
		skyboxRenderer.RenderSkybox(camera);
		waterBuffers.UnbindFrameBuffer();

		renderer.RenderTerrains(terrains, terrainShader, lights, camera);
		renderer.RenderEntities(entities, staticShader, lights, camera);
		if (camera.GetState() != CameraStates::FP)
			renderer.RenderEntity(&player, staticShader, lights, camera);
		waterRenderer.Render(waters, camera, lights);
		skyboxRenderer.RenderSkybox(camera);
		DisplayManager::EndLoop();
	}

	DisplayManager::Destroy();
	InputManager::Destroy();
	system("pause");
	return 0;
}