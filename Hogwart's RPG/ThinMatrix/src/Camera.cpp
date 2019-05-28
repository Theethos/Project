#include "pch.h"
#include "Camera.h"

Camera::Camera() :
	m_Position(0, 0, 0)
{
	
}

Camera::~Camera()
{

}

void Camera::Move()
{
	if (InputManager::IsKeyPressed(SDL_SCANCODE_W))
	{
		m_Position.z -= 0.05f;
	}
	if (InputManager::IsKeyPressed(SDL_SCANCODE_S))
	{
		m_Position.z += 0.05f;
	}
	if (InputManager::IsKeyPressed(SDL_SCANCODE_A))
	{
		m_Position.x -= 0.05f;
	}
	if (InputManager::IsKeyPressed(SDL_SCANCODE_D))
	{
		m_Position.x += 0.05f;
	}
	if (InputManager::IsKeyPressed(SDL_SCANCODE_SPACE))
	{
		m_Position.y += 0.05f;
	}
	if (InputManager::IsKeyPressed(SDL_SCANCODE_LSHIFT))
	{
		m_Position.y -= 0.05f;
	}
}