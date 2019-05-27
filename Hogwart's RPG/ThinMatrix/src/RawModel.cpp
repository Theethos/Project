#include "pch.h"
#include "RawModel.h"

RawModel::RawModel(const unsigned & vaoID, const unsigned & vertexCount) :
	m_VaoID(vaoID),
	m_VertexCount(vertexCount)
{
}

RawModel::~RawModel()
{
}
