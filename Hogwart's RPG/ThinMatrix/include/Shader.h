#ifndef SHADER_H
#define SHADER_H

#include "Light.h"

class Shader
{
public:
	// Constructors
	Shader(const std::string & vertexShaderPath, const std::string & fragmentShaderPath);
	Shader(const std::string & shaderName);
	// Destructor
	~Shader();
	void					Bind() const;
	void					Unbind() const;
	void					ConnectTextureUnits();
	unsigned				GetUniformLocation(const char * variableName);
	inline const unsigned	GetID() const { return m_ProgramID; }

	inline void				LoadFloat(const char * location, const float & data) { glUniform1f(GetUniformLocation(location), data); }
	inline void				LoadInt(const char * location, const int & data) { glUniform1i(GetUniformLocation(location), data); }
	inline void				LoadBool(const char * location, const bool & data) { glUniform1i(GetUniformLocation(location), (int)data); }
	inline void				LoadVector(const char * location, const glm::vec3 & data) { glUniform3f(GetUniformLocation(location), data.x, data.y, data.z); }
	inline void				LoadMatrix(const char * location, const glm::mat4 & data) { glUniformMatrix4fv(GetUniformLocation(location), 1, GL_FALSE, value_ptr(data)); }
	inline void				LoadLight(Light & light) { LoadVector("lightPosition", light.GetPosition()); LoadVector("lightColor", light.GetColor()); }
	inline void				LoadShineVariable(const float & shininess, const float & reflectivity) { LoadFloat("shininess", shininess); LoadFloat("reflectivity", reflectivity); }

private:
	// Private functions
	const std::string		LoadSourceFromFile(const char * path);
	unsigned				CompileShader(unsigned type, const char * source);
	void					CreateShader(const char * vertexShader, const char * fragmentShader);
	
	// Attributes
	unsigned m_ProgramID, m_VertexID, m_FragmentID;
	std::map < std::string, unsigned> m_UniformLocations;
};

#endif //!SHADER_H