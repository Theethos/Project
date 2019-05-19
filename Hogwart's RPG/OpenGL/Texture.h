#ifndef TEXTURE_H
#define TEXTURE_H

class Texture
{
public:
	Texture(std::string path);
	~Texture();

	void Bind(const unsigned slot = 0) const;
	void Unbind() const;

	inline const unsigned &GetWidth() const { return m_Width; }
	inline const unsigned &GetHeight() const { return m_Height; }

private:
	unsigned m_TextureID;
	std::string m_Path;
	SDL_Surface * m_Texture;
	unsigned m_Width, m_Height, m_BPP;
};

#endif // !TEXTURE_H
