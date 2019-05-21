#ifndef TEXTURE_H
#define TEXTURE_H

class ModelTexture
{
public:
	ModelTexture(unsigned textureID);
	~ModelTexture();

	inline const unsigned GetTextureID() const { return m_TextureID; }

private:
	unsigned m_TextureID;
};


#endif // !TEXTURE_H
