#include "pch.h"
#include "Renderer.h"
#include "Axis.h"
#include "Crate.h" // Cube.h, Shader.h

/*		AXIS
		y
		|
		|_____x
	   / 
	 z/			*/

int main(int argc, char * argv[])
{
	DisplayManager::Create();
	InputManager::Create(); 
	TextureManager::Create();

	Shader shaderCouleur("Shaders/couleur3D.vert", "Shaders/couleur3D.frag");
	Shader shaderTexture("Shaders/texture.vert", "Shaders/texture.frag");

	Axis axis(2.f, shaderCouleur);

	TextureManager::LoadFromFile("Textures/crate/crate13.jpg", "crateTexture");

	Crate crate(1.f, shaderTexture, TextureManager::GetTexture("crateTexture"));

	// OpenGL version
	std::cout << glGetString(GL_VERSION) << std::endl;

	// Main loop
	while (DisplayManager::ShouldBeRunning())
	{
		InputManager::Update();
		DisplayManager::Clear();

		axis.Draw();

		crate.Draw();
		DisplayManager::MoveCamera();

		DisplayManager::Display();
	}

	TextureManager::Destroy();
	InputManager::Destroy();
	DisplayManager::Destroy();
	return 0;
}