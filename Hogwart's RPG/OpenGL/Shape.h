#ifndef SHAPE_H
#define SHAPE_H

#include "Shader.h"

class Shape
{
public:
	// Constructor
	Shape();
	// Destructor
	virtual ~Shape();

	inline const float *GetVertices() const { return m_Positions; }
	inline const unsigned *GetIndices() const { return m_Indices; }
	inline const std::pair<unsigned, unsigned> &GetCount() const { return m_Count; }

protected:
	float *m_Positions;
	unsigned *m_Indices;
	std::pair<unsigned, unsigned> m_Count;

	// Private functions
	virtual void InitPositions() = 0;
	virtual void InitIndices() = 0;
};

class Cube : public Shape
{
public:
	Cube();
	~Cube();

private:
	void InitPositions();
	void InitIndices();
};

#endif // !SHAPE_H
