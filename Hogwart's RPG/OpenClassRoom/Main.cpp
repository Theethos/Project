#include "pch.h"
#include "SceneTP.h"
#include "FrameBuffer.h"

/*		AXIS			TEXTURE COORDINATES
		y				(0,1)_______(1,1)
		|				  |			  |
		|_____x			  |			  |
	   /				  |___________|
	 z/					(0,0)		(1,0)	*/

int main(int argc, char * argv[])
{
	for (unsigned i = 0; i < argc; ++i)
		std::cout << argv[i] << std::endl;

	SceneTP::Run();
	DisplayManager::Create();
	InputManager::Create(); 
	TextureManager::Create();
	
	Shader shaderTexture("Shaders/texture.vert", "Shaders/texture.frag");
	Shader shaderColor("Shaders/couleur3D.vert", "Shaders/couleur3D.frag");

	FrameBuffer fbo(512, 512, 4.f, &shaderTexture);

	Crate crate(2.f, shaderTexture, LoadTex("Textures/crate/crate12.jpg", "crateTexture"));
	Cube cube(1.f, shaderColor);

	float angle(0.f);

	// OpenGL version
	std::cout << glGetString(GL_VERSION) << std::endl;

	// Main loop
	while (DisplayManager::ShouldBeRunning())
	{
		DisplayManager::StartLoop();

	/*	fbo.StartDrawingInto();

			angle > 360.f ? angle -= 360.f : angle += 0.001f;

			fbo.PushMatrix();
				fbo.SetModelView(glm::rotate(fbo.GetModelView(), angle, glm::vec3(0, 1, 0)));
				crate.Draw(fbo.GetModelView(), fbo.GetProjection());
			fbo.PopMatrix();


		fbo.EndDrawingInto(DisplayManager::GetWidth(), DisplayManager::GetHeight(), true);			*/

		crate.Draw();
		//cube.Draw();

		DisplayManager::EndLoop();
	}

	TextureManager::Destroy();
	InputManager::Destroy();
	DisplayManager::Destroy();
	return 0;
}