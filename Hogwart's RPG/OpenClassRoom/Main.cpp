#include "pch.h"
#include "DisplayManager.h"
#include "Renderer.h"
#include "Axis.h"
#include "Cube.h" // Shader.h

/*		AXIS
		y
		|
		|_____x
	   / 
	 z/			*/

int main(int argc, char * argv[])
{
	DisplayManager::Create();
	EventManager::Create(); 

	Shader shader("Shaders/couleur3D.vert", "Shaders/couleur3D.frag");

	Cube cube(1.f, shader);
	Axis axis(2.f, shader);

	// OpenGL version
	std::cout << glGetString(GL_VERSION) << std::endl;

	// Main loop
	while (DisplayManager::ShouldBeRunning())
	{
		EventManager::Update();
		DisplayManager::Clear();

		// Draw the axis
		axis.Draw(DisplayManager::ModelView, DisplayManager::Projection);

		// Draw a cube
		cube.Draw(DisplayManager::ModelView, DisplayManager::Projection);

		DisplayManager::Display();
	}

	EventManager::Destroy();
	DisplayManager::Destroy();
	return 0;
}