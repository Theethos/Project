#include "Precompiled_Header_OpenGL.h"
#include "ShaderOPG.h"

// Constructor
Shader::Shader(const std::string & vertexShaderPath, const std::string & fragmentShaderPath)
{
	CreateShader(LoadSourceFromFile(vertexShaderPath).c_str(), LoadSourceFromFile(fragmentShaderPath).c_str());
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

// Private functions
// Load the source code from a file to a string
std::string Shader::LoadSourceFromFile(const std::string & path)
{
	std::ifstream file(path);
	if (file.is_open())
	{
		std::string line, source;
		while (getline(file, line, '/'))							// The delimiter is not in the file, so getline() gets all the file 
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

		glBindAttribLocation(m_ProgramID, 0, "in_Positions");
		glBindAttribLocation(m_ProgramID, 1, "in_Color");
		glBindAttribLocation(m_ProgramID, 2, "in_TextureCoords");

		glLinkProgram(m_ProgramID);
		glValidateProgram(m_ProgramID);
	}
}
