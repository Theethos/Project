#include "pch.h"
#include "Shader.h"

// Constructor
Shader::Shader(const std::string & vertexShaderPath, const std::string & fragmentShaderPath)
{
	this->CreateShader(LoadSourceFromFile(("res/shaders/" + vertexShaderPath + ".vert").c_str()).c_str(), LoadSourceFromFile(("res/shaders/" + fragmentShaderPath + ".frag").c_str()).c_str());
	this->Bind();
	this->LoadMatrix("projectionMatrix", DisplayManager::GetProjectionMatrix());
	this->Unbind();
}
Shader::Shader(const std::string & shaderName)
{
	this->CreateShader(LoadSourceFromFile(("res/shaders/" + shaderName + ".vert").c_str()).c_str(), LoadSourceFromFile(("res/shaders/" + shaderName + ".frag").c_str()).c_str());
	this->Bind();
	this->LoadMatrix("projectionMatrix", DisplayManager::GetProjectionMatrix());
	this->Unbind();
}
// Destructor
Shader::~Shader()
{
	glUseProgram(0);
	glDetachShader(m_ProgramID, m_VertexID);
	glDetachShader(m_ProgramID, m_FragmentID);
	glDeleteShader(m_VertexID);
	glDeleteShader(m_FragmentID);
	glDeleteProgram(m_ProgramID);
}

void Shader::Bind() const
{
	glUseProgram(m_ProgramID);
}

void Shader::Unbind() const
{
	glUseProgram(0);
}

// Function for the terrains textures
void Shader::ConnectTextureUnits()
{
	LoadInt("bgColor", 0);
	LoadInt("rColor", 1);
	LoadInt("gColor", 2);
	LoadInt("bColor", 3);
	LoadInt("blendMap", 4);
}

// Private functions
// Load the source code from a file to a string
const std::string Shader::LoadSourceFromFile(const char * path)
{
	std::ifstream file(path);
	if (file.is_open())
	{
		std::string line, source;
		while (getline(file, line, '§'))							// The delimiter is not in the file, so getline() gets all the file 
		{
			source += line;
		}
		file.close();
		return source;
	}
	std::cerr << "Can't open the file " << path << std::endl;
	return "";
}

// Compile the source code
unsigned Shader::CompileShader(unsigned type, const char * source)
{
	unsigned id = glCreateShader(type);
	glShaderSource(id, 1, &source, nullptr);
	glCompileShader(id);											// Compile the source code

	// Check if the compilation went well
	int compilation_status;
	glGetShaderiv(id, GL_COMPILE_STATUS, &compilation_status);
	if (compilation_status != GL_TRUE)
	{
		int length;
		char log[1024];
		glGetShaderInfoLog(id, 1024, &length, log);
		std::cout << "Error while compiling in the file " << source << ", line " << __LINE__ << " : " << log << std::endl;

		glDeleteShader(id);
		return 0;
	}
	return id;
}

// Link the vertex and fragment shader into a program
void Shader::CreateShader(const char * vertexShader, const char * fragmentShader)
{
	if (vertexShader && fragmentShader)
	{
		m_VertexID		= CompileShader(GL_VERTEX_SHADER, vertexShader);
		m_FragmentID	= CompileShader(GL_FRAGMENT_SHADER, fragmentShader);
		m_ProgramID		= glCreateProgram();

		glAttachShader(m_ProgramID, m_VertexID);
		glAttachShader(m_ProgramID, m_FragmentID);

		glLinkProgram(m_ProgramID);
		glValidateProgram(m_ProgramID);
	}
}

unsigned Shader::GetUniformLocation(const char * variableName)
{
	m_UniformLocations[variableName] = glGetUniformLocation(m_ProgramID, variableName);
	return m_UniformLocations[variableName];
}

