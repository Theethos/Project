#include "pch.h"
#include "DisplayManager.h"
#include "Renderer.h"
#include "Shader.h"

int main(int argc, char * argv[])
{
	DisplayManager::Create();
	EventManager::Create(); 

	std::vector<float> vertices = {
		0.0f, 0.0f, -1.f,
		0.5f, 0.0f, -1.f,
		0.0f, 0.5f, -1.f
	};

	std::vector<float> colors = {
		1.f, 0.f, 0.f,
		0.f, 1.f, 0.f,
		0.f, 0.f, 1.f,
	};

	Shader shader("Shaders/couleur3D.vert", "Shaders/couleur3D.frag");

	// OpenGL version
	std::cout << glGetString(GL_VERSION) << std::endl;

	// Main loop
	while (DisplayManager::ShouldBeRunning())
	{
		DisplayManager::Clear();
		EventManager::Update();
		
		shader.Bind();

		// Envoie des vertices
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, vertices.data());
		glEnableVertexAttribArray(0);
		
		// Envoie des couleurs
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, colors.data());
		glEnableVertexAttribArray(1);
			
		DisplayManager::ModelView = glm::translate(DisplayManager::ModelView, glm::vec3(0.4, 0.0, 0.0));
		//DisplayManager::ModelView = glm::rotate(DisplayManager::ModelView, 60.0f, glm::vec3(0.0, 0.0, 1.0));
		//DisplayManager::ModelView = glm::scale(DisplayManager::ModelView, glm::vec3(2.0, 2.0, 1.0));
		
		// Envoie des matrices
		glUniformMatrix4fv(glGetUniformLocation(shader.GetID(), "modelview"), 1, GL_FALSE, value_ptr(DisplayManager::ModelView));
		glUniformMatrix4fv(glGetUniformLocation(shader.GetID(), "projection"), 1, GL_FALSE, value_ptr(DisplayManager::Projection));

		glDrawArrays(GL_TRIANGLES, 0, vertices.size() / 3);

		glDisableVertexAttribArray(1);
		glDisableVertexAttribArray(0);

		shader.Unbind();

		DisplayManager::Display();
	}

	EventManager::Destroy();
	DisplayManager::Destroy();
	return 0;
}