#include "pch.h"
#include "DisplayManager.h"
#include "Renderer.h"
#include "Shader.h"

int main()
{
	DisplayManager::Create();
	EventManager::Create(); 

	std::vector<float> axis = {
		//	/ X-axis			/ Red
		0.f, 0.f, 0.f,		1.f, 0.f, 0.f,
		0.5f, 0.f, 0.f,		1.f, 0.f, 0.f,
		//	/ Y-axis			/ Green
		0.f, 0.f, 0.f,		0.f, 1.f, 0.f,
		0.f, 0.5f, 0.f,		0.f, 1.f, 0.f,
		//	/ Z-axis			/ Blue
		0.f, 0.f, 0.f,		0.f, 0.f, 1.f,
		0.f, 0.f, 0.5f,		0.f, 0.f, 1.f,
	};

	std::vector<float> vertices = {
		-1.f, -1.f, -1.f,	 1.f, -1.f, -1.f,    1.f,  1.f, -1.f,   // Face 1-1
		-1.f, -1.f, -1.f,	 1.f,  1.f, -1.f,   -1.f,  1.f, -1.f,	// Face 1-2

		 1.f, -1.f,  1.f,    1.f,  1.f, -1.f,	 1.f, -1.f, -1.f,	// Face 2-1
		 1.f, -1.f,  1.f,	 1.f,  1.f,  1.f,    1.f,  1.f, -1.f,   // Face 2-2

		-1.f, -1.f,  1.f,	 1.f, -1.f,  1.f,    1.f, -1.f, -1.f,   // Face 3-1
		-1.f, -1.f,  1.f,	 1.f, -1.f, -1.f,   -1.f, -1.f, -1.f,   // Face 3-2

		-1.f,  1.f,  1.f,   -1.f, -1.f,  1.f,    1.f, -1.f,  1.f,   // Face 4-1
		-1.f,  1.f,  1.f,    1.f,  1.f,  1.f,    1.f, -1.f,  1.f,   // Face 4-2

		-1.f, -1.f,  1.f,   -1.f,  1.f,  1.f,   -1.f,  1.f, -1.f,	// Face 5-1
		-1.f, -1.f,  1.f,   -1.f, -1.f, -1.f,   -1.f,  1.f, -1.f,	// Face 5-2

		-1.f,  1.f, -1.f,    1.f,  1.f, -1.f,    1.f,  1.f,  1.f,	// Face 6-1
		-1.f,  1.f, -1.f,   -1.f,  1.f,  1.f,    1.f,  1.f,  1.f	// Face 6-2
	};


	std::vector<float> colors = {
		// Face arrière		-> Rouge
		1.f,  0.f,  0.f,    1.f,  0.f,  0.f,   1.f,  0.f,  0.f,
		1.f,  0.f,  0.f,    1.f,  0.f,  0.f,   1.f,  0.f,  0.f,
		// Face droite			-> Vert
		0.f,  1.f,  0.f,    0.f,  1.f,  0.f,   0.f,  1.f,  0.f,
		0.f,  1.f,  0.f,    0.f,  1.f,  0.f,   0.f,  1.f,  0.f,
		// Face avant			-> Bleu
		0.f,  0.f,  1.f,    0.f,  0.f,  1.f,   0.f,  0.f,  1.f,
		0.f,  0.f,  1.f,    0.f,  0.f,  1.f,   0.f,  0.f,  1.f,
		// Face gauche		-> Jaune
		0.f,  1.f,  1.f,	0.f,  1.f,  1.f,   0.f,  1.f,  1.f,
		0.f,  1.f,  1.f,    0.f,  1.f,  1.f,   0.f,  1.f,  1.f,
		// Face dessus			-> Orange
		1.f,  1.f,  0.f,    1.f,  1.f,  0.f,   1.f,  1.f,  0.f,
		1.f,  1.f,  0.f,    1.f,  1.f,  0.f,   1.f,  1.f,  0.f,
		// Face dessous		-> Rose
		1.f,  0.f,  1.f,    1.f,  0.f,  1.f,   1.f,  0.f,  1.f,
		1.f,  0.f,  1.f,    1.f,  0.f,  1.f,   1.f,  0.f,  1.f
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
		
		/// Affichage des axes
		// Envoie des vertices
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, axis.data());
		glEnableVertexAttribArray(0);

		// Envoie des couleurs
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, axis.data() + 3);
		glEnableVertexAttribArray(1);

		// Envoie des matrices
		glUniformMatrix4fv(glGetUniformLocation(shader.GetID(), "modelview"), 1, GL_FALSE, value_ptr(DisplayManager::ModelView));
		glUniformMatrix4fv(glGetUniformLocation(shader.GetID(), "projection"), 1, GL_FALSE, value_ptr(DisplayManager::Projection));

		glDrawArrays(GL_LINES, 0, axis.size() / 3);

		glDisableVertexAttribArray(1);
		glDisableVertexAttribArray(0);
		/// !Affichage des axes

		// Envoie des vertices
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, vertices.data());
		glEnableVertexAttribArray(0);
		
		// Envoie des couleurs
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, colors.data());
		glEnableVertexAttribArray(1);
		
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