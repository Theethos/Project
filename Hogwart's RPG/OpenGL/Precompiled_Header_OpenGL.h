#ifndef PRECOMPILED_HEADER
#define PRECOMPILED_HEADER

//SFML
#include "SFML/Config.hpp"
#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"
#include "SFML/Network.hpp"
#include "SFML/System.hpp"

// OpenGL stuff
#include <glew.h>

// STD stuff
#include <iostream>
#include <string>
#include <cstdlib>
#include <fstream>
#include <array>
#include <vector>
#include <exception>

// Macros 
//////////////////////////////////////////////////////////////
/// Display OpenGL errors (TheChernoProject code on YouTube)
///
//////////////////////////////////////////////////////////////
#define ASSERT(x) if (!(x)) __debugbreak();
#define GET_GL_ERROR(x) GLClearError();\
	x;\
	ASSERT(GLLogCall(#x, __FILE__, __LINE__))

inline void GLClearError() { while (glGetError() != GL_NO_ERROR); }
inline bool GLLogCall(const char * function, const char * file, const int line)
{
	while (GLenum error = glGetError())
	{
		std::cerr << "Error in " << file << ", line " << line << " -> [OpenGL Error] (" << error << ")" << std::endl;
		return false;
	}
	return true;
}

#endif // !PRECOMPILED_HEADER
