#include "Precompiled_Header_OpenGL.h"

static std::string LoadSourceFromFile(const std::string& path)
{
	std::ifstream file(path);
	if (file.is_open())
	{
		std::string line, source;
		while (getline(file, line, '/'))					// Le délimiteur n'est pas dans le fichier, donc getline() récupère tout
		{
			source += line;
		}
		file.close();
		return source;
	}
	std::cerr << "Can't open the file " << path << std::endl;
	return "";
}


static unsigned CompileShader(unsigned type, const char * source)
{
	unsigned id = glCreateShader(type);
	glShaderSource(id, 1, &source, nullptr);
	glCompileShader(id);										// Compile le vertexShader

	int compilation_status;
	glGetShaderiv(id, GL_COMPILE_STATUS, &compilation_status);
	if (compilation_status != GL_TRUE)
	{
		int length;
		char log[1024];
		glGetShaderInfoLog(id, 1024, &length, log);
		std::cout << "Error line " << __LINE__ << " : " << log << std::endl;

		glDeleteShader(id);
		return 0;
	}
	return id;
}


static unsigned CreateShader(const char * vertexShader, const char * fragmentShader)
{
	if (vertexShader && fragmentShader)
	{
		unsigned program			= glCreateProgram();
		unsigned vertex_shader		= CompileShader(GL_VERTEX_SHADER, vertexShader);
		unsigned fragment_shader	= CompileShader(GL_FRAGMENT_SHADER, fragmentShader);

		glAttachShader(program, vertex_shader);
		glAttachShader(program, fragment_shader);
		glLinkProgram(program);
		glValidateProgram(program);

		glDeleteShader(vertex_shader);
		glDeleteShader(fragment_shader);

		return program;
	}
	return 0;
}

static void UpdateColor(float &r, float &g, float &b, int &timer)
{
	if (timer == 0)
	{
		r = 1.f;
	}
	else if (timer == 100)
	{
		r = 0.f;
		g = 1.f;
	}
	else if (timer == 200)
	{
		g = 0.f;
		b = 1.f;
	}
	else if (timer == 300)
	{
		r = 1.f;
		g = 1.f;
		b = 0.f;
	}
	else if (timer == 400)
	{
		g = 0.f;
		b = 1.f;
	}
	else if (timer == 500)
	{
		r = 0.f;
		g = 1.f;
	}
	else if (timer == 600)
	{
		timer = -1;
		r = 0.f;
		g = 0.f;
		b = 0.f;
	}
	++timer;
}

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
	
	
	const char *vertexShader = LoadSourceFromFile("../External/Shader/Basic.vtx").c_str();
	const char *fragmentShader = LoadSourceFromFile("../External/Shader/Basic.frg").c_str();

	unsigned shader = CreateShader(vertexShader, fragmentShader);
	glUseProgram(shader);

	// Récupération de la variable uniforme u_Color dans le fragmentShader
	int u_Color = glGetUniformLocation(shader, "u_Color");
	if (u_Color == -1) return -1;
	float r = 0.f, g = 0.f, b = 0.f;
	int timer = 0.f;

	// Loop until the user closes the window 
	while (!glfwWindowShouldClose(window))
	{
		// Render here 
		glClear(GL_COLOR_BUFFER_BIT);
		
		glUniform4f(u_Color, r, g, b, 1.f);
		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, nullptr);			// Dessine les triangles à partir des indices; nullptr car on a déjà bind notre indexBuffer

		// Swap front and back buffers 
		glfwSwapBuffers(window);

		// Poll for and process events 
		glfwPollEvents();

		UpdateColor(r, g, b, timer);
	}

	glDeleteProgram(shader);
	glfwTerminate();
	return 0;
}