#include "Precompiled_Header_OpenGL.h"
#include "Shape.h"

/// ///////////////////////////////////////////////////////////
//							SHAPE							 //
/// ///////////////////////////////////////////////////////////
Shape::Shape() :
m_Positions(nullptr),
m_Indices(nullptr)
{}

Shape::~Shape()
{
	if (m_Positions)
		delete m_Positions;
	if (m_Indices)
		delete m_Indices;
}

/// ///////////////////////////////////////////////////////////
//							CUBE							 //
/// ///////////////////////////////////////////////////////////
Cube::Cube() :
Shape()
{
	InitPositions();
	InitIndices();
}

Cube::~Cube()
{}

void Cube::InitPositions()
{
	m_Positions = new float[24]
	{
		-0.5f, -0.5f,  0.5f,	// 0 Left  bottom front
		-0.5f, -0.5f, -0.5f,	// 1 Left  bottom back
		-0.5f,  0.5f,  0.5f,	// 2 Left  top	  front
		-0.5f,  0.5f, -0.5f,	// 3 Left  top	  back
		 0.5f, -0.5f,  0.5f,	// 4 Right bottom front
		 0.5f, -0.5f, -0.5f,	// 5 Right bottom back
		 0.5f,	0.5f,  0.5f,	// 6 Right top	  front
		 0.5f,  0.5f, -0.5f,	// 7 Right top	  back
	};

	m_Count.first = 24;
}

void Cube::InitIndices()
{
	m_Indices = new unsigned[36]
	{
		0, 6, 2,	0, 6, 4,	// Front
		0, 3, 1,	0, 3, 2,	// Left
		3, 5, 1,	3, 5, 7,	// Back
		5, 6, 7,	5, 6, 4,	// Right
		6, 3, 2,	6, 3, 7,	// Top
		5, 0, 1,	5, 0, 4		// Bottom
	};

	m_Count.second = 36;
}
