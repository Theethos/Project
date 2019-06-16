#include "pch.h"
#include "Player.h"

float Player::Speed = 20.f;
float Player::TurnSpeed = 100.f;
float Player::Gravity = -50.f;
float Player::JumpPower = 30.f;

Player::Player(const TexturedModel & model, const glm::vec3 & position, const glm::vec3 & rotation, const float & scale) :
	Entity(model, position, rotation, scale),
	m_CurrentSpeedForward(0),
	m_CurrentSpeedSideway(0),
	m_CurrentTurnSpeed(0),
	m_UpwardSpeed(0),
	m_BaseUpTranslation(position.y),
	m_IsInAir(false)
{
}

Player::~Player()
{
}

void Player::Move(const Terrain & terrain, const double & dt)
{
	m_CurrentSpeedForward = 0;
	if (GetKey(SDL_SCANCODE_W))
		m_CurrentSpeedForward = Speed;
	if (GetKey(SDL_SCANCODE_S))
		m_CurrentSpeedForward = -Speed;
	
	m_CurrentSpeedSideway = 0;
	if (GetKey(SDL_SCANCODE_A))
		m_CurrentSpeedSideway = -Speed;
	if (GetKey(SDL_SCANCODE_D))
		m_CurrentSpeedSideway = Speed;

	m_CurrentTurnSpeed = 0;
	if (GetKey(SDL_SCANCODE_Q))
		m_CurrentTurnSpeed = TurnSpeed;
	if (GetKey(SDL_SCANCODE_E))
		m_CurrentTurnSpeed = -TurnSpeed;

	if (GetKey(SDL_SCANCODE_SPACE) && !m_IsInAir)
	{
		m_UpwardSpeed = JumpPower;
		m_IsInAir = true;
	}

	IncreaseRotation(0, m_CurrentTurnSpeed * dt, 0);
	float distance_forward = m_CurrentSpeedForward * dt;
	float distance_sideway = m_CurrentSpeedSideway * dt;
	float dx = distance_forward * sin(glm::radians(m_Rotation.y)) - distance_sideway * cos(glm::radians(m_Rotation.y));
	float dz = distance_forward * cos(glm::radians(m_Rotation.y)) + distance_sideway * sin(glm::radians(m_Rotation.y));
	m_UpwardSpeed += Gravity * dt;
	IncreasePosition(dx, 0, dz);
	float terrain_height = terrain.GetHeightOfTerrain(m_Position.x, m_Position.z);
	IncreasePosition(0, m_UpwardSpeed * dt, 0);
	if (m_Position.y < terrain_height)
	{
		m_UpwardSpeed = 0; 
		m_IsInAir = false;
		m_Position.y = terrain_height;
	}
}
