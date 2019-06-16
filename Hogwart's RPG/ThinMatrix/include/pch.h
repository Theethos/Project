//////////////////////////////////////////////////////
/// Precompiled header
/// Contains all the usefull headers for the project
//////////////////////////////////////////////////////

#pragma once

// OpenGL
#include "glad/glad.h"
#include "glm/glm.hpp"
#include "glm/gtx/transform.hpp"
#include "glm/gtc/type_ptr.hpp"

// Assimp includes
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

// SDL
#include <SDL2/SDL.h>
#include <SDL2/SDL_Image.h>

// STL
#include <cstdlib>
#include <sstream>
#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include <chrono>
#include <map>
#include <math.h>
#include <array>
#include <initializer_list>

// Other libs
#include "stb_image.h"

// Managers / Static classes
#include "DisplayManager.h"
#include "InputManager.h"
#include "MyMaths.h"
#include "Macros.h"

