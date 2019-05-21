#pragma once
/////////////////////////////////////////////////////
/// \brief Static class that manages the rendering
///
////////////////////////////////////////////////////

class Renderer
{
public:

	static void RenderArrays(const std::vector<float> & data, unsigned dataDimension = 3, unsigned attributeID = 0, bool draw = true, GLenum GLenumMode = GL_TRIANGLES, GLenum GLenumType = GL_FLOAT)
	{
		glVertexAttribPointer(attributeID, dataDimension, GLenumType, GL_FALSE, 0, data.data());
		glEnableVertexAttribArray(attributeID);
		if (draw)
			glDrawArrays(GLenumMode, 0 , data.size() / dataDimension);
	}

	inline static void Clear() { glClear(GL_COLOR_BUFFER_BIT); }

private:
	Renderer() = delete;
	~Renderer() = delete;
};

