#ifndef SHADER_H
#define SHADER_H

class Shader
{
public:
	// Constructor
	Shader(const char * vertexShaderPath, const char * fragmentShaderPath);
	// Destructor
	virtual ~Shader();
	void Bind() const;
	void Unbind() const;

	inline const unsigned GetID() const { return m_ProgramID; }
private:
	unsigned m_ProgramID, m_VertexID, m_FragmentID;

	// Private functions
	const std::string	LoadSourceFromFile(const char * path);
	unsigned			CompileShader(unsigned type, const char * source);
	void				CreateShader(const char * vertexShader, const char * fragmentShader);
};

#endif //!SHADER_H