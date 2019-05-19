#include "Precompiled_Header_OpenGL.h"
#include "Shape.h"
#include "Renderer.h"
#include "Texture.h"

/*static bool running = true, resize = false;
int w_w = 800, w_h = 600;
void RenderingLoop(sf::RenderWindow *window);

int main(void)
{
	// Set the window and the OpenGL contexte
	sf::ContextSettings settings(24, 8, 0, 3, 3);
	sf::RenderWindow window(sf::VideoMode(w_w, w_h), "Hogwart's RPG in OpenGL", sf::Style::Default, settings);
	window.setVerticalSyncEnabled(true);

	// Initialize glew
	if (glewInit() != GLEW_OK)
	{
		std::cout << "Can't initialize GLEW. Error line " << __LINE__ << std::endl;
		return -1;
	}
	window.setActive(false);

	// Launch rendering loop
	sf::Thread renderingThread(&RenderingLoop, &window);
	renderingThread.launch();

	sf::Event event;
	// Event / Logic loop
	while (running)
	{
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				running = false;
			else if (event.type == sf::Event::Resized)
			{
				// on ajuste le viewport lorsque la fenêtre est redimensionnée
				resize = true;
				w_w = event.size.width; w_h = event.size.height;
			}
			else if (event.type == sf::Event::KeyReleased)
			{
				if (event.key.code == sf::Keyboard::Escape)
					running = false;
			}
		}
	}

	renderingThread.wait();
	return 0;
}

void RenderingLoop(sf::RenderWindow *window)
{	
	window->setActive(true);

	window->resetGLStates();
	glEnable(GL_DEPTH_TEST);
	glClearDepth(1.f);
	glViewport(0, 0, window->getSize().x, window->getSize().y);


	Shader shader("../External/Shader/Basic.vtx", "../External/Shader/Basic.frg");
	Cube cube;

	VertexArray va;
	VertexBuffer vb(cube.GetVertices(), cube.GetCount().first * sizeof(float));

	VertexBufferLayout layout;
	layout.Push<float>(3);
	va.BindBufferLayout(vb, layout);

	IndexBuffer ib(cube.GetIndices(), cube.GetCount().second);

	Renderer renderer;

	window->setActive(false);

	sf::Texture texture;
	texture.loadFromFile("caisse.jpg");
	

	// Loop until the user closes the window 
	while (running)
	{
		// Render here
		window->setActive(true);
		if (resize)
		{
			glViewport(0, 0, w_w, w_h);
			resize = false;
		}
		renderer.Clear();

		// Bind a texture
		sf::Texture::bind(&texture);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glDrawArrays(GL_TRIANGLES, 34 * 34, 36);

		renderer.Draw(va, ib, shader);

		window->setActive(false);

		window->display();

	}
	window->close();
}*/

// 1000 loops	: 17114 avec thread, 17157 sans thread
// 10000 loops	: 167015 avec thread, 167070 sans thread (sans toucher à rien donc le nombre d'event est minime voire nul)