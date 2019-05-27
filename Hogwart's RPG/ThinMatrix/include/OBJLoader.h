#pragma once

#include "Loader.h"

class OBJLoader
{
public:
	static RawModel LoadFromFile(const std::string & objPath, Loader & loader);

private:
	OBJLoader();
	~OBJLoader();
};

