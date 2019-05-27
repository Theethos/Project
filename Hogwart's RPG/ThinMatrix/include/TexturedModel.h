#pragma once

#include "RawModel.h"
#include "ModelTexture.h"

class TexturedModel
{
public:
	TexturedModel(const RawModel & model, const ModelTexture & texture);
	~TexturedModel();

	inline const RawModel GetRawModel() const { return m_Model; }
	inline const ModelTexture GetModelTexture() const { return m_Texture; }

private:
	RawModel m_Model;
	ModelTexture m_Texture;
};

