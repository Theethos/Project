#include "pch.h"
#include "Light.h"

Light::Light(const glm::vec3 & position, const glm::vec3 & color) :
	m_Position(position),
	m_Color(color)
{}

Light::~Light()
{}
