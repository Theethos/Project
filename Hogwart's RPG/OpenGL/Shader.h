#ifndef SHADER_H
#define SHADER_H

enum class ColorState { BLACK, RED, ORANGE, YELLOW, GREEN, LIGHT_GREEN, LIGHT_BLUE, BLUE, VIOLET, PINK};
////////////////////////////////////////////////////////
/// This class does not come from ThinMatrix tutorial, so
/// if there is a problem someday, look his video about
/// shaders (the 5th one) and see the differences.
////////////////////////////////////////////////////////
class Shader
{
public:
	// Constructor
	Shader(const std::string& vertexShaderPath, const std::string& fragmentShaderPath);
	// Destructor
	virtual ~Shader();
	void Bind() const;
	void Unbind() const;
	void UpdateColor();

private:
	unsigned m_Program;
	int u_Color;
	float r, g, b;
	ColorState m_ColorState;

	// Private functions
	std::string LoadSourceFromFile(const std::string& path);
	unsigned	CompileShader(unsigned type, const char * source);
	unsigned	CreateShader(const char * vertexShader, const char * fragmentShader);
};

#endif //!SHADER_H