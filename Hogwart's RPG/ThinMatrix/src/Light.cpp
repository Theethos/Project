#include "pch.h"
#include "Light.h"

Light::Light(const glm::vec3 & position, const glm::vec3 & color, const glm::vec3 & attenuation) :
	m_Position(position),
	m_Color(color),
	m_Attenuation(attenuation)
{}

Light::~Light()
{}
