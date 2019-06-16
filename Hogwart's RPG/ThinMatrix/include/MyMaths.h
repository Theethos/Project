#pragma once

#include "Camera.h"

//////////////////////////////////////////////
/// Static class for the maths in the project
//////////////////////////////////////////////

class Maths
{
public:
	static float BarryCentric(const glm::vec3 & p1, const glm::vec3 & p2, const glm::vec3 & p3, const glm::vec2 & pos)
	{
		float det = (p2.z - p3.z) * (p1.x - p3.x) + (p3.x - p2.x) * (p1.z - p3.z);
		float l1 = ((p2.z - p3.z) * (pos.x - p3.x) + (p3.x - p2.x) * (pos.y - p3.z)) / det;
		float l2 = ((p3.z - p1.z) * (pos.x - p3.x) + (p1.x - p3.x) * (pos.y - p3.z)) / det;
		float l3 = 1.0f - l1 - l2;
		return l1 * p1.y + l2 * p2.y + l3 * p3.y;
	}
	static glm::mat4 CreateTransformationMatrix(const glm::vec2 & transformation, const glm::vec2 & scale)
	{
		glm::mat4 matrix(1.f);
		matrix = glm::translate(matrix, glm::vec3(transformation, 0.f));
		matrix = glm::scale(matrix, glm::vec3(scale.x, scale.y, 1.f));
		return matrix;
	}
	static glm::mat4 CreateTransformationMatrix(const glm::vec3 & transformation, const glm::vec3 & rotation, const float & scale)
	{
		glm::mat4 matrix(1.f);
		matrix = glm::translate(matrix, transformation);
		matrix = glm::rotate(matrix, glm::radians(rotation.x), glm::vec3(1, 0, 0));
		matrix = glm::rotate(matrix, glm::radians(rotation.y), glm::vec3(0, 1, 0));
		matrix = glm::rotate(matrix, glm::radians(rotation.z), glm::vec3(0, 0, 1));
		matrix = glm::scale(matrix, glm::vec3(scale, scale, scale));
		return matrix;
	}
	static glm::mat4 CreateViewMatrix(Camera & camera)
	{
		glm::mat4 matrix(1.f);
		matrix = glm::rotate(matrix, glm::radians(camera.GetPitch()), { 1, 0, 0 });
		matrix = glm::rotate(matrix, glm::radians(camera.GetYaw()), { 0, 1, 0 });
		matrix = glm::translate(matrix, - camera.GetPosition());
		return matrix;
		//return glm::lookAt(camera.GetPosition(), camera.GetPlayer().GetPosition(), glm::vec3(0, 1, 0));
	}
private:
	Maths() = delete;
	~Maths() = delete;
};
