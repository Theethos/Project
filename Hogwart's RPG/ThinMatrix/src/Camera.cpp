#include "pch.h"
#include "Camera.h"

Camera::Camera(Player & player) :
	m_Player(player),
	m_Position(0, 0, 0),
	m_Pitch(-10.f),
	m_DistanceFromPlayer(30.f),
	m_AngleAroundPlayer(0.f)
{
	
}

Camera::~Camera()
{

}

void Camera::Move(const double & dt)
{
	CalculateZoom();
	CalculatePitch();
	CalculateAngleAroundPlayer();
	CalculateCameraPosition();
}

inline float Camera::CalculateHorizontalDistance()
{
	return m_DistanceFromPlayer * cos(m_Pitch);
}
inline float Camera::CalculateVerticalDistance()
{
	return m_DistanceFromPlayer * sin(m_Pitch);
}
inline void Camera::CalculateCameraPosition()
{
	auto & player_position = m_Player.GetPosition();
	float horizontal = CalculateHorizontalDistance();
	float theta = m_Player.GetRotation().y + m_AngleAroundPlayer;
	m_Position.x = player_position.x + horizontal * sin(theta);
	m_Position.y = std::max(player_position.y + CalculateVerticalDistance(), 0.1f);
	m_Position.z = player_position.z + horizontal * cos(theta);

}

inline void Camera::CalculateZoom()
{
	m_DistanceFromPlayer -= InputManager::GetMouseWheelY();
	if (m_DistanceFromPlayer < 0.5)
		m_DistanceFromPlayer = 0.5;
}

inline void Camera::CalculatePitch()
{
	if (GetButton(SDL_BUTTON_RIGHT))
		m_Pitch -= InputManager::GetMouseRelativePosition().y * 0.001;
}

inline void Camera::CalculateAngleAroundPlayer()
{
	if (GetButton(SDL_BUTTON_LEFT))
		m_AngleAroundPlayer -= InputManager::GetMouseRelativePosition().x * 0.001;
	if (m_AngleAroundPlayer != 0 && (GetKey(SDL_SCANCODE_Q) || GetKey(SDL_SCANCODE_E)))
		m_AngleAroundPlayer = 0;
}
