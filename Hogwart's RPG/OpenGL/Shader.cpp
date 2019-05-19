#include "Precompiled_Header_OpenGL.h"
#include "Shader.h"

// Constructor
Shader::Shader(const std::string& vertexShaderPath, const std::string& fragmentShaderPath)
{
	m_Program = CreateShader(LoadSourceFromFile(vertexShaderPath).c_str(), LoadSourceFromFile(fragmentShaderPath).c_str());

	u_Color = glGetUniformLocation(m_Program, "u_Color");
	r = 0.f; g = 0.f; b = 0.f;
	m_ColorState = ColorState::BLACK;
}
// Destructor
Shader::~Shader()
{
	glDeleteProgram(m_Program);
}

void Shader::Bind() const
{
	glUseProgram(m_Program);
}

void Shader::Unbind() const
{
	glUseProgram(0);
}

// Functions
void Shader::UpdateColor()
{
	switch (m_ColorState)
	{
	case ColorState::BLACK:
		r += (1.f / 255.f);
		if (r >= 1.f) m_ColorState = ColorState::RED;
		break;
	case ColorState::RED:
		g += (1.f / 255.f);
		if (g >= 0.5f) m_ColorState = ColorState::ORANGE;
		break;
	case ColorState::ORANGE:
		g += (1.f / 255.f);
		if (g >= 1.0f) m_ColorState = ColorState::YELLOW;
		break;
	case ColorState::YELLOW:
		r -= (1.f / 255.f);
		if (r <= 0.f) m_ColorState = ColorState::GREEN;
		break;
	case ColorState::GREEN:
		b += (1.f / 255.f);
		if (b >= 0.5f) m_ColorState = ColorState::LIGHT_GREEN;
		break;
	case ColorState::LIGHT_GREEN:
		b += (1.f / 255.f);
		if (b >= 1.f) m_ColorState = ColorState::LIGHT_BLUE;
		break;
	case ColorState::LIGHT_BLUE:
		g -= (1.f / 255.f);
		if (g <= 0.f) m_ColorState = ColorState::BLUE;
		break;
	case ColorState::BLUE:
		r += (1.f / 255.f);
		if (r >= 0.5f) m_ColorState = ColorState::VIOLET;
		break;
	case ColorState::VIOLET:
		r += (1.f / 255.f);
		if (r >= 1.f) m_ColorState = ColorState::PINK;
		break;
	case ColorState::PINK:
		r -= (1.f / 255.f);
		b -= (1.f / 255.f);
		if (r <= 0.f && b <= 0.f) m_ColorState = ColorState::BLACK;
		break;
	default:
		break;
	}
	glUniform4f(u_Color, r, g, b, 1.f);
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
unsigned Shader::CreateShader(const char * vertexShader, const char * fragmentShader)
{
	if (vertexShader && fragmentShader)
	{
		unsigned program			= glCreateProgram();
		unsigned vertex_shader		= CompileShader(GL_VERTEX_SHADER, vertexShader);
		unsigned fragment_shader	= CompileShader(GL_FRAGMENT_SHADER, fragmentShader);

		glAttachShader(program, vertex_shader);
		glAttachShader(program, fragment_shader);
		glLinkProgram(program);
		glValidateProgram(program);

		glDeleteShader(vertex_shader);
		glDeleteShader(fragment_shader);

		return program;
	}
	return 0;
}