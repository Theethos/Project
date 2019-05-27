#pragma once

// Class that store a model to be rendered 
class RawModel
{
public:
	RawModel(const unsigned & vaoID, const unsigned & vertexCount);
	~RawModel();

	inline const unsigned GetVaoID() const { return m_VaoID; }
	// VertexCount -> vector.size()
	inline const unsigned GetVertexCount() const { return m_VertexCount; }

private:
	unsigned m_VaoID;
	unsigned m_VertexCount;
};

