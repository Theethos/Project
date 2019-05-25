#include "pch.h"
#include "ShapesHeader.h"

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// Static class that runs the TP made on OpenClassRooms that you can find on this link
/// https://openclassrooms.com/fr/courses/966823-developpez-vos-applications-3d-avec-opengl-3-3/964079-tp-une-relique-retrouvee
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class SceneTP
{
public:
	static void Run()
	{
		DisplayManager::Create();
		InputManager::Create();
		TextureManager::Create();

		Shader shaderCouleur("Shaders/couleur3D.vert", "Shaders/couleur3D.frag");
		Shader shaderTexture("Shaders/texture.vert", "Shaders/texture.frag");

		Crate crate(1.f, shaderTexture, LoadTex("Textures/crate/crate13.jpg", "crateTexture"));
		Crate crate2(1.f, shaderTexture, LoadTex("Textures/crate/crate12.jpg", "crateTexture2"));
		Crystal crystal(shaderTexture, LoadTex("Textures/crystal/crystal.tga", "crystalTexture"));
		Hut hut(shaderTexture, LoadTex("Textures/bricks/brick009.jpg", "wallTexture"), LoadTex("Textures/roof/roof06b.jpg", "roofTexture"));
		GrassGround grassGround(30.f, shaderTexture, LoadTex("Textures/vegetal/veg007.jpg", "grassTexture"));
		DirtGround dirtGround(5.f, shaderTexture, LoadTex("Textures/parquet/checker17.jpg", "dirtTexture"));

		// OpenGL version
		std::cout << glGetString(GL_VERSION) << std::endl;

		// Main loop
		while (DisplayManager::ShouldBeRunning())
		{
			DisplayManager::StartLoop();

			// Draw the grass
			grassGround.Draw();									// -> 1rs level -> We should push & pop to save the level but hear it is useless

			// Draw the floor on the grass					
			MV = glm::translate(MV, glm::vec3(0, 0.0001f, 0));  // -> 2nd level
			dirtGround.Draw();
			// Draw the hut
			hut.Draw();

			MV = glm::translate(MV, glm::vec3(0, 0.0001f, 0));  // -> 3rd level
			// Draw the crates
			MV = glm::translate(MV, glm::vec3(0, 0.5f, 0));
			crate.Draw();
			Push;
				MV = glm::translate(MV, glm::vec3(1.5f, 0.f, -1.5f));
				crate2.Draw();
				MV = glm::translate(MV, glm::vec3(-3.f, 0.f, 0.f));
				crate2.Draw();
			Pop;

			// Draw the crystal
			MV = glm::translate(MV, glm::vec3(0, 1.6f, 0));
			crystal.Animate();
			crystal.Draw();

			DisplayManager::EndLoop();
		}
		TextureManager::Destroy();
		InputManager::Destroy();
		DisplayManager::Destroy();
	}
};

