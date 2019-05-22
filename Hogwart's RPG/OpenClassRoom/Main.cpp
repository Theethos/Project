#include "pch.h"
#include "DisplayManager.h"
#include "Renderer.h"
#include "Axis.h"
#include "Cube.h" // Shader.h
#include "Texture.h"


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

	Shader shader("Shaders/texture.vert", "Shaders/texture.frag");

	Cube cube(1.f, shader);
	Axis axis(2.f, shader);
	Texture caisse;
	caisse.LoadFromFile("Textures/Caisse.jpg");

	std::vector<float> vertices = {
		-2, -2, -2,   2, -2, -2,   2, 2, -2,
		-2, -2, -2,   -2, 2, -2,   2, 2, -2 
	};

	std::vector<float> coordTexture = {
		0.f, 0.f,	1.f, 0.f,	1.f, 1.f,
		0.f, 0.f,	0.f, 1.f,	1.f, 1.f,

	};

	// OpenGL version
	std::cout << glGetString(GL_VERSION) << std::endl;

	// Main loop
	while (DisplayManager::ShouldBeRunning())
	{
		InputManager::Update();
		DisplayManager::Clear();
		
		shader.Bind();

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, vertices.data());
		glEnableVertexAttribArray(0);

		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, coordTexture.data());
		glEnableVertexAttribArray(2);

		glUniformMatrix4fv(glGetUniformLocation(shader.GetID(), "projection"), 1, GL_FALSE, glm::value_ptr(DisplayManager::Projection));
		glUniformMatrix4fv(glGetUniformLocation(shader.GetID(), "modelview"), 1, GL_FALSE, glm::value_ptr(DisplayManager::ModelView));

		glBindTexture(GL_TEXTURE_2D, caisse.GetID());

		glDrawArrays(GL_TRIANGLES, 0, vertices.size() / 3);

		glBindTexture(GL_TEXTURE_2D, 0);

		glDisableVertexAttribArray(2);
		glDisableVertexAttribArray(0);

		shader.Unbind();

		DisplayManager::Display();
	}

	InputManager::Destroy();
	DisplayManager::Destroy();
	return 0;
}