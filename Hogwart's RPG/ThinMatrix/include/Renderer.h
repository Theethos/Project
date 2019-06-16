#pragma once

#include "Shader.h"
#include "Entity.h"
#include "Terrain.h"

class Renderer
{
public:
	Renderer();
	~Renderer();

	void RenderEntity(const Entity * entity, Shader & shader, std::vector<Light> & light, Camera & camera, const glm::vec4 & plane = { 0, 0, 0, 0 });
	void RenderEntities(const std::map<TexturedModel, std::vector<Entity *>> & entities, Shader & shader, std::vector<Light> & light, Camera & camera, const glm::vec4 & plane = { 0, 0, 0, 0 });
	void RenderTerrains(const std::vector<Terrain> & terrains, Shader & shader, std::vector<Light> & light, Camera & camera, const glm::vec4 & plane = { 0, 0, 0, 0 });

private:
	static unsigned int NUMBER_LIGHT;
};

