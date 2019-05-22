#include "pch.h"
#include "Camera.h"

Camera::Camera() :
	m_Speed(0.05f),
	m_Sensitivity(0.05f),
	m_Phi(0.f),
	m_Theta(0.f),
	m_Orientation(3,3,3),
	m_VerticalAxis(0, 0, 1),
	m_Position(),
	m_Target(0,0,0),
	m_LateralMotion()
{
	m_Orientation = m_Target - m_Position;
	m_Orientation = glm::normalize(m_Orientation);

	InitAngles();
}

Camera::Camera(glm::vec3 eyes, glm::vec3 center, glm::vec3 up) :
	m_Speed(0.05f),
	m_Sensitivity(0.05f),
	m_Phi(0.f),
	m_Theta(0.f),
	m_Orientation(),
	m_VerticalAxis(up),
	m_Position(eyes),
	m_Target(center),
	m_LateralMotion()
{
	m_Orientation = m_Target - m_Position;
	m_Orientation = glm::normalize(m_Orientation);

	InitAngles();
}

Camera::~Camera()
{
}

void Camera::InitAngles()
{
	if (m_VerticalAxis.x)
	{
		m_Phi = asin(m_Orientation.x);
		m_Theta = acos(m_Orientation.y / cos(m_Phi));

		if (m_Orientation.y < 0)
			m_Theta *= -1.f;
	}
	else if (m_VerticalAxis.y)
	{
		m_Phi = asin(m_Orientation.y);
		m_Theta = acos(m_Orientation.z / cos(m_Phi));

		if (m_Orientation.z < 0)
			m_Theta *= -1.f ;
	}
	else if (m_VerticalAxis.z)
	{
		m_Phi = asin(m_Orientation.x);
		m_Theta = acos(m_Orientation.z / cos(m_Phi));

		if (m_Orientation.x < 0)
			m_Theta *= -1.f;
	}

	m_Phi *= (180 / M_PI);
	m_Theta *= (180 / M_PI);
}

void Camera::Orientate()
{
	// Update angles
	m_Phi -= (InputManager::GetMouseRelativePosition().y * m_Sensitivity);
	m_Theta -= (InputManager::GetMouseRelativePosition().x * m_Sensitivity);

	// Limitation of the angle for calculation
	if (m_Phi > 89.f) m_Phi = 89.f;
	else if (m_Phi < -89.f) m_Phi = -89.f;

	// Update the orientation vector depending on the vertical axis
	UpdateOrientation();

	// Update the lateral motion
	m_LateralMotion = glm::cross(m_VerticalAxis, m_Orientation);
	m_LateralMotion = glm::normalize(m_LateralMotion);

	// Update target point
	m_Target = m_Orientation + m_Position;
}

void Camera::Move()
{
	if (InputManager::DidMouseMove())
		Orientate();

	// QWERTY INPUTS
	if (InputManager::IsKeyPressed(SDL_SCANCODE_W))
	{
		m_Position += (m_Orientation * m_Speed);
		m_Target = m_Position + m_Orientation;
	}
	if (InputManager::IsKeyPressed(SDL_SCANCODE_S))
	{
		m_Position -= (m_Orientation * m_Speed);
		m_Target = m_Position + m_Orientation;
	}
	if (InputManager::IsKeyPressed(SDL_SCANCODE_A))
	{
		m_Position += (m_LateralMotion * m_Speed);
		m_Target = m_Position + m_Orientation;
	}
	if (InputManager::IsKeyPressed(SDL_SCANCODE_D))
	{
		m_Position -= (m_LateralMotion * m_Speed);
		m_Target = m_Position + m_Orientation;
	}
}

void Camera::LookAt()
{
	DisplayManager::ModelView = glm::lookAt(m_Position, m_Target, m_VerticalAxis);
}

void Camera::UpdateOrientation()
{
	// Converting the angles in radian
	float phi_radian = m_Phi * M_PI / 180;
	float theta_radian = m_Theta * M_PI / 180;

	if (m_VerticalAxis.x)
	{
		m_Orientation.x = sin(phi_radian);
		m_Orientation.y = cos(phi_radian) * cos(theta_radian);
		m_Orientation.z = cos(phi_radian) * sin(theta_radian);
	}
	else if (m_VerticalAxis.y)
	{
		m_Orientation.x = cos(phi_radian) * sin(theta_radian);
		m_Orientation.y = sin(phi_radian);
		m_Orientation.z = cos(phi_radian) * cos(theta_radian);
	}
	else if (m_VerticalAxis.z)
	{
		m_Orientation.y = cos(phi_radian) * cos(theta_radian);
		m_Orientation.z = cos(phi_radian) * sin(theta_radian);
		m_Orientation.x = sin(phi_radian);
	}
}
