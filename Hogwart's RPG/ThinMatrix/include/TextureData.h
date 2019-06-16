#pragma once
class TextureData
{
public:
	TextureData(unsigned char * data, const unsigned int & width, const unsigned int & height);
	~TextureData();

	inline unsigned char *	GetData() const { return m_Data; }
	inline unsigned int		GetHeight() const { return m_Height; }
	inline unsigned int		GetWidth() const { return m_Width; }

private:
	unsigned char * m_Data;
	unsigned int m_Width, m_Height;
};

