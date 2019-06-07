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

	// Have to do this to use TexturedModel instances as std::map keys (doesn't really mean something)
	bool operator<(const TexturedModel & other) const
	{
		return m_Model.GetVaoID() < other.m_Model.GetVaoID();
	}

private:
	RawModel m_Model;
	ModelTexture m_Texture;
};

