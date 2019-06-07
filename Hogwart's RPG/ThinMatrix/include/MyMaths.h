#pragma once

#include "Camera.h"

//////////////////////////////////////////////
/// Static class for the maths in the project
//////////////////////////////////////////////

class Maths
{
public:
	static glm::mat4 CreateTransformationMatrix(const glm::vec3 & transformation, const glm::vec3 & rotation, const float & scale)
	{
		glm::mat4 matrix(1.f);
		matrix = glm::translate(matrix, transformation);
		matrix = glm::rotate(matrix, rotation.x, glm::vec3(1, 0, 0));
		matrix = glm::rotate(matrix, rotation.y, glm::vec3(0, 1, 0));
		matrix = glm::rotate(matrix, rotation.z, glm::vec3(0, 0, 1));
		matrix = glm::scale(matrix, glm::vec3(scale, scale, scale));
		return matrix;
	}
	static glm::mat4 CreateViewMatrix(Camera & camera)
	{
		return glm::lookAt(camera.GetPosition(), camera.GetPlayer().GetPosition(), glm::vec3(0, 1, 0));
	}
private:
	Maths() = delete;
	~Maths() = delete;
};
