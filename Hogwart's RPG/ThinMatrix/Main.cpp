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
#undef main // SDL macro to create a main function
////////////////////////////////////////////////////////////////////////////////////////
/// \brief Entry point of the application
/// \return Application exit code 
////////////////////////////////////////////////////////////////////////////////////////
int main(int argc, char * argv[])
{
	DisplayManager::Create();
	InputManager::Create();

	Loader loader;
	Shader shader("res/shaders/texture.vert", "res/shaders/texture.frag");
	Renderer renderer(shader);

	/*std::vector<float> positions = {
		-0.5f, 0.5f,-0.5f,
		-0.5f,-0.5f,-0.5f,
		 0.5f,-0.5f,-0.5f,
		 0.5f, 0.5f,-0.5f,

		-0.5f, 0.5f, 0.5f,
		-0.5f,-0.5f, 0.5f,
		 0.5f,-0.5f, 0.5f,
		 0.5f, 0.5f, 0.5f,

		 0.5f, 0.5f,-0.5f,
		 0.5f,-0.5f,-0.5f,
		 0.5f,-0.5f, 0.5f,
		 0.5f, 0.5f, 0.5f,

		-0.5f, 0.5f,-0.5f,
		-0.5f,-0.5f,-0.5f,
		-0.5f,-0.5f, 0.5f,
		-0.5f, 0.5f, 0.5f,

		-0.5f, 0.5f, 0.5f,
		-0.5f, 0.5f,-0.5f,
		 0.5f, 0.5f,-0.5f,
		 0.5f, 0.5f, 0.5f,

		-0.5f,-0.5f, 0.5f,
		-0.5f,-0.5f,-0.5f,
		 0.5f,-0.5f,-0.5f,
		 0.5f,-0.5f, 0.5f
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

	std::vector<unsigned int> indices = {
			0,1,3,
			3,1,2,
			
			4,5,7,
			7,5,6,
			
			8,9,11,
			11,9,10,
			
			12,13,15,
			15,13,14,
			
			16,17,19,
			19,17,18,
			
			20,21,23,
			23,21,22
	};*/


	RawModel model = OBJLoader::LoadFromFile("res/obj_file/stall.obj", loader);
	//RawModel model = loader.LoadToVAO(positions, indices, textureCoords);
	ModelTexture texture(loader.LoadTexture("res/obj_file/stall.png"));
	TexturedModel texModel(model, texture);
	
	Entity entity(texModel, glm::vec3(0, 0, -25), glm::vec3(0, 0, 0), 1.f);
	Light light(glm::vec3(0, 0, -20), glm::vec3(1, 1, 1));

	Camera camera;

	while (DisplayManager::ShouldBeRunning())
	{
		DisplayManager::StartLoop();

		entity.IncreaseRotation(0, 0.05, 0);

		camera.Move();

		shader.Bind();

		shader.LoadLight(light);
		shader.LoadMatrix("viewMatrix", Maths::CreateViewMatrix(camera));

		renderer.Render(entity);

		shader.Unbind();

		DisplayManager::EndLoop();
	}

	DisplayManager::Destroy();
	InputManager::Destroy();
	return 0;
}