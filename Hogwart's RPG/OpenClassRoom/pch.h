#pragma once

// OpenGL
#include "glm/glm.hpp"
#include "glm/gtx/transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "glew.h"

// SDL
#include "SDL.h"
#include "SDL_image.h"

// STL
#include <cstdlib>
#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include <chrono>
#include <map>
#include <math.h>

// Managers
#include "DisplayManager.h"
#include "InputManager.h"
#include "TextureManager.h"

// Macros
#ifndef BUFFER_OFFSET
	#define BUFFER_OFFSET(offset) ((char*)NULL + (offset)) 
#endif // !BUFFER_OFFSET
