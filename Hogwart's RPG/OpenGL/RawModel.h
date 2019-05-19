#pragma once
class RawModel
{
public:
	RawModel(unsigned vaoID, unsigned vertexCount);
	~RawModel();

	inline const unsigned GetVaoID() const { return m_VaoID; }
	inline const unsigned GetVertexCount() const { return m_VertexCount; }
private:
	unsigned m_VaoID;
	unsigned m_VertexCount;
};

