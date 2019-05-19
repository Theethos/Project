#ifndef RENDERER_H
#define RENDERER_H

#include "TextureModel.h"

class Renderer
{
public:
	Renderer();
	~Renderer();

	void Clear();
	void Render(TextureModel & textureModel);
	void Render(RawModel & rawModel);
};

#endif // !RENDERER_H
