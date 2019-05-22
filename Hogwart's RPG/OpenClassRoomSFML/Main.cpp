#include "pch.h"
#include "DisplayManager.h"
#include "Renderer.h"
#include "Cube.h"	// Shader.h
#include "Axis.h"

int main()
{
	DisplayManager::Create();
	EventManager::Create();

	Shader shader("Shaders/couleur3D.vert", "Shaders/couleur3D.frag");

	Cube cube(1.f, shader);
	Axis axis(2.f, shader);

	float rotationAngle(0.f);

	// OpenGL version
	std::cout << glGetString(GL_VERSION) << std::endl;

	// Main loop
	while (DisplayManager::ShouldBeRunning())
	{
		EventManager::Update();
		DisplayManager::Clear();

		// Draw the axis
		//axis.Draw(DisplayManager::ModelView, DisplayManager::Projection);

		rotationAngle >= 360.f ? rotationAngle = 0.f : rotationAngle += 0.01f;

		DisplayManager::ModelView = glm::rotate(DisplayManager::ModelView, rotationAngle, glm::vec3(0, 1, 0));

		// Draw a cube
		cube.Draw(DisplayManager::ModelView, DisplayManager::Projection);

		DisplayManager::Display();
	}

	EventManager::Destroy();
	DisplayManager::Destroy();
	return 0;
}