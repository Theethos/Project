#pragma once

#include "Shader.h"
#include "Entity.h"
#include "Terrain.h"

class Renderer
{
public:
	Renderer();
	~Renderer();

	void RenderEntity(const Entity * entity, Shader & shader, Light & light, Camera & camera);
	void RenderEntities(const std::map<TexturedModel, std::vector<Entity *>> & entities, Shader & shader, Light & light, Camera & camera);
	void RenderTerrains(const std::vector<Terrain> & terrains, Shader & shader, Light & light, Camera & camera);

private:
};

