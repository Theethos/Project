#include "pch.h"
#include "Camera.h"

float Camera::SPEED = 20.f;

Camera::Camera(Player & player) :
	m_Player(player),
	m_Position(0, 0, 0),
	m_Pitch(20.f),
	m_Yaw(0),
	m_DistanceFromPlayer(30.f),
	m_AngleAroundPlayer(0.f),
	m_State(CameraStates::TP)
{
	
}

Camera::~Camera()
{

}

void Camera::Move(const Terrain & terrain, const double & dt)
{
	CheckSwitchState();
	if (m_State == CameraStates::TP)
	{
		CalculateZoom();
		CalculatePitch();
		CalculateAngleAroundPlayer();
		CalculateCameraPosition(terrain);
		m_Yaw = 180 - (m_Player.GetRotation().y + m_AngleAroundPlayer);
	}
	else if (m_State == CameraStates::Free)
	{
		// Move the camera the same way that we move the player
		m_CurrentSpeedForward = 0;
		if (GetKey(SDL_SCANCODE_UP))
			m_CurrentSpeedForward = SPEED;
		if (GetKey(SDL_SCANCODE_DOWN))
			m_CurrentSpeedForward = - SPEED;

		m_CurrentSpeedSideway = 0;
		if (GetKey(SDL_SCANCODE_LEFT))
			m_CurrentSpeedSideway = - SPEED;
		if (GetKey(SDL_SCANCODE_RIGHT))
			m_CurrentSpeedSideway = SPEED;
		
		if (GetKey(SDL_SCANCODE_LCTRL))
			m_Position.y += SPEED * dt;
		if (GetKey(SDL_SCANCODE_LALT))
			m_Position.y -= SPEED * dt;

		// Apply the right movement to both axis
		float distance_forward = m_CurrentSpeedForward * dt;
		float distance_sideway = m_CurrentSpeedSideway * dt;
		float dx = distance_forward * sin(glm::radians(180 - m_Yaw)) - distance_sideway * cos(glm::radians(180 - m_Yaw));
		float dz = distance_forward * cos(glm::radians(180 - m_Yaw)) + distance_sideway * sin(glm::radians(180 - m_Yaw));
		m_Position += glm::vec3(dx, 0.f, dz);

		// Update the pitch and yaw
		auto mouse_rel = InputManager::GetMouseRelativePosition();
		m_Yaw += mouse_rel.x * 0.03;
		m_Pitch += mouse_rel.y * 0.03;
		float height = terrain.GetHeightOfTerrain(m_Position.x, m_Position.z) + 0.1;
		
		if (m_Position.y < height)
			m_Position.y = height;
	}
	else if (m_State == CameraStates::FP)
	{
		// Put the camera in the face of the character
		m_Position = m_Player.GetPosition() + glm::vec3(0, 8, 0);
		// Get the movement of the mouse
		auto mouse_rel = InputManager::GetMouseRelativePosition();
		// Update yaw and pitch with those values
		if (InputManager::DidMouseMove())
		{
			m_Yaw += mouse_rel.x * 0.02;
			m_Player.SetRotation({ 0.f, 180 - m_Yaw, 0.f });
		}
		else
			m_Yaw = 180 - (m_Player.GetRotation().y + m_AngleAroundPlayer);
		m_Pitch += mouse_rel.y * 0.02;
		if (m_Pitch > 37.f)
			m_Pitch = 37.f;
		else if (m_Pitch < -89.f)
			m_Pitch = -89.f;
	}
}

inline float Camera::CalculateHorizontalDistance()
{
	return m_DistanceFromPlayer * cos(glm::radians(m_Pitch));
}
inline float Camera::CalculateVerticalDistance()
{
	return m_DistanceFromPlayer * sin(glm::radians(m_Pitch));
}
inline void Camera::CalculateCameraPosition(const Terrain & terrain)
{
	auto & player_position = m_Player.GetPosition();
	float horizontal = CalculateHorizontalDistance();
	float theta = m_Player.GetRotation().y + m_AngleAroundPlayer;
	m_Position.x = player_position.x - horizontal * sin(glm::radians(theta));
	m_Position.z = player_position.z - horizontal * cos(glm::radians(theta));
	float vertical = CalculateVerticalDistance();
	m_Position.y = std::max(player_position.y + vertical, terrain.GetHeightOfTerrain(m_Position.x, m_Position.z) + vertical);

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
		m_Pitch -= InputManager::GetMouseRelativePosition().y * 0.1f;
}

inline void Camera::CalculateAngleAroundPlayer()
{
	if (GetButton(SDL_BUTTON_LEFT))
		m_AngleAroundPlayer -= InputManager::GetMouseRelativePosition().x * 0.3f;
	if ((m_AngleAroundPlayer != 0) && GetKey(SDL_SCANCODE_Q) || GetKey(SDL_SCANCODE_E))
		m_AngleAroundPlayer = 0;
}

void Camera::CheckSwitchState()
{
	if (GetKeyOnce(SDL_SCANCODE_F1) && m_State == CameraStates::TP)
	{
		m_AngleAroundPlayer = 180;
	}
	if (GetKeyOnce(SDL_SCANCODE_F2))
	{
		if (m_State == CameraStates::TP)
		{
			m_State = CameraStates::Free;
		}
		else if (m_State == CameraStates::Free)
		{
			m_Pitch = 5.f;
			m_State = CameraStates::FP;
		}
		else if (m_State == CameraStates::FP)
		{
			m_Pitch = 20.f;
			m_State = CameraStates::TP;
		}
	}
}
