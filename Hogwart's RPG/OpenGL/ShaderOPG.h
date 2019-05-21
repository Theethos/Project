#ifndef SHADER_H
#define SHADER_H

class Shader
{
public:
	// Constructor
	Shader(const std::string& vertexShaderPath, const std::string& fragmentShaderPath);
	// Destructor
	virtual ~Shader();
	void Bind() const;
	void Unbind() const;

private:
	unsigned m_ProgramID, m_VertexID, m_FragmentID;

	// Private functions
	std::string LoadSourceFromFile(const std::string& path);
	unsigned	CompileShader(unsigned type, const char * source);
	void		CreateShader(const char * vertexShader, const char * fragmentShader);
};

#endif //!SHADER_H