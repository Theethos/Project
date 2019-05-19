////////////////////////////////////////////////////////////
/// This project is an adaptation in C++ of the tutorials
///	about OpenGL made by ThinMatrix in Java. You can find
/// these tutorials on his YouTube Channel :
/// https://www.youtube.com/playlist?list=PLRIWtICgwaX0u7Rf9zkZhLoLuZVfUksDP
////////////////////////////////////////////////////////////

#include "Precompiled_Header_OpenGL.h"
#include "DisplayManager.h"
#include "Loader.h"
#include "Renderer.h"
#include "Shader.h"
//#include "TextureModel.h"

////////////////////////////////////////////////////////////
/// Entry point of application
///
/// \return Application exit code
///
////////////////////////////////////////////////////////////
int main(int argc, char * argv[])
{
	DisplayManager::Create();
	EventManager::Create();

	Loader loader;
	Renderer renderer;
	Shader shader("../External/Shaders/Basic.vtx", "../External/Shaders/Basic.frg");

	std::vector<float> positions = {
		-0.5f,  0.5f, 0.f,
		-0.5f, -0.5f, 0.f,
		 0.5f, -0.5f, 0.f,
		 0.5f,  0.5f, 0.f,
	};

	std::vector<unsigned> indices = {
		0, 1, 3,
		3, 1, 2
	};

	std::vector<float> textureCoords = {
		0.f, 0.f,
		0.f, 1.f,
		1.f, 1.f,
		1.f, 0.f,
	};

	RawModel rawModel = loader.LoadToVAO(positions, indices, textureCoords);
	/*sf::Texture * texture = loader.LoadTexture("./texture.jpg");
	TextureModel textureModel(model, texture);*/

	// Main loop
	while (DisplayManager::ShouldBeRunning())
	{
		renderer.Clear();
		EventManager::Update();
		shader.Bind();
		renderer.Render(rawModel);
		DisplayManager::Update();
	}
	
	loader.CleanUp();
	EventManager::Destroy();
	DisplayManager::Destroy();
	return 0;
}