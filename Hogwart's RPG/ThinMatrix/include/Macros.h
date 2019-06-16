#pragma once

namespace ToolBox
{
	template<typename T>
	inline void Display(std::initializer_list<T> list)
	{
		for (auto & it : list)
		{
			std::cout << it << " ";
		}
		std::cout << std::endl;
	}

	inline void Display(std::initializer_list<glm::vec3> list)
	{
		for (auto & it : list)
		{
			std::cout << it.x << " " << it.y << " " << it.z << " ";
		}
		std::cout << std::endl;
	}
}