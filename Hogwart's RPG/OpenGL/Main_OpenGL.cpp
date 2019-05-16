#include "Precompiled_Header_OpenGL.h"
#include "Shader.h"

int main(void)
{
	float cube[] =
	{
		-0.5f, -0.5f,  0.5f,	// 0 left bottom front
		-0.5f, -0.5f, -0.5f,	// 1 left bottom back
		-0.5f,  0.5f,  0.5f,	// 2 left top front
		-0.5f,  0.5f, -0.5f,	// 3 left top back
		 0.5f, -0.5f,  0.5f,	// 4 right bottom front
		 0.5f, -0.5f, -0.5f,	// 5 right bottom back
		 0.5f,	0.5f,  0.5f,	// 6 right top front
		 0.5f,  0.5f, -0.5f,	// 7 right top back
	};

	unsigned indices[] =
	{
		// Front
		0, 6, 2,
		0, 6, 4,
		// Left
		0, 3, 1,
		0, 3, 2,
		// Back
		3, 5, 1,
		3, 5, 7,
		// Right
		5, 6, 7,
		5, 6, 4,
		// Top
		6, 3, 2,
		6, 3, 7,
		// Bottom
		5, 0, 1,
		5, 0, 4
	};

	GLFWwindow* window;
	// Initialize the library 
	if (!glfwInit())
	{
		std::cout << "Can't initialize GLFW. Error line " << __LINE__ << std::endl;
		return -1;
	}
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Create a windowed mode window and its OpenGL context 
	window = glfwCreateWindow(640, 480, "Hogwart's RPG with OpenGL", nullptr, nullptr);
	if (!window)
	{
		glfwTerminate();
		return -1;
	}

	// Make the window's context current 
	glfwMakeContextCurrent(window);
	
	// Limite les frames
	glfwSwapInterval(1);

	// Initialize glew
	if (glewInit() != GLEW_OK)
	{
		std::cout << "Can't initialize GLEW. Error line " << __LINE__ << std::endl;
		return -1;
	}
	
	unsigned vertexArray;
	glGenVertexArrays(1, &vertexArray);
	glBindVertexArray(vertexArray);

	// Crée et sélectionne un buffer pour nos triangles
	unsigned buffer;														// ID du buffer
	glGenBuffers(1, &buffer);												// Génère un buffer et renvoie son ID
	glBindBuffer(GL_ARRAY_BUFFER, buffer);									// Sélectionne le buffer (ID) choisi
	glBufferData(GL_ARRAY_BUFFER, sizeof(cube), cube, GL_STATIC_DRAW);		// Place les données à dessiner dans le buffer (la vram)

	// Relie le buffer et vertexArray
	glEnableVertexAttribArray(0);											
	glVertexAttribPointer(0, 3, GL_FLOAT, 0, 3 * sizeof(float), 0);			// Dit à OpenGL comment exploiter nos données : /arg1 : L'index de l'attribut que l'on utilise dans le vertex (ici
																			// il n'y a qu'un attribut donc on commence à 0. /arg2 : Le nombre d'élément par vertice,
																			// /arg3 : type de donnée, /arg4 : Booléen pour normaliser (entre 0 et 1), /arg5 : L'écart entre 2 attributs (en bytes)
																			// /arg6 : Le début de la zone mémoire de l'attribut.
	
	// Crée et sélectionne un buffer contenant les indices des vertex au dessus (pour les stocker qu'une seule fois)
	unsigned indexBuffer;
	glGenBuffers(1, &indexBuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
	
	
	Shader shader("../External/Shader/Basic.vtx", "../External/Shader/Basic.frg");
	glUseProgram(shader.program());

	// Loop until the user closes the window 
	while (!glfwWindowShouldClose(window))
	{
		// Render here 
		glClear(GL_COLOR_BUFFER_BIT);
		
		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, nullptr);			// Dessine les triangles à partir des indices; nullptr car on a déjà bind notre indexBuffer

		// Swap front and back buffers 
		glfwSwapBuffers(window);

		// Poll for and process events 
		glfwPollEvents();

		shader.UpdateColor();
	}

	glfwTerminate();
	return 0;
}