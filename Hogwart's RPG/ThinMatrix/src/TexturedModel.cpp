#include "pch.h"
#include "TexturedModel.h"

TexturedModel::TexturedModel(const RawModel & model, const ModelTexture & texture) :
	m_Model(model),
	m_Texture(texture)
{
}

TexturedModel::~TexturedModel()
{
}
