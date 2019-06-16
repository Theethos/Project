#pragma once

#include "Player.h"

enum class CameraStates { FP, TP, Free };

class Camera
{
public:
	Camera(Player & player);
	~Camera();

	void Move(const Terrain & terrain, const double & dt);
	
	inline const Player & GetPlayer() const { return m_Player; }
	inline glm::vec3 & GetPosition() { return m_Position; }
	inline const float GetPitch() const { return m_Pitch; }
	inline const float GetYaw() const { return m_Yaw; }
	inline const CameraStates GetState() const { return m_State; }
	inline void InvertPitch() { m_Pitch = - m_Pitch; }
	inline void	SetPositionY(const float & value) { m_Position.y = value; }


private:
	static float SPEED;
	Player & m_Player;
	glm::vec3 m_Position;
	float m_DistanceFromPlayer, m_AngleAroundPlayer, m_Pitch, m_Yaw, m_CurrentSpeedForward, m_CurrentSpeedSideway;
	CameraStates m_State;

	inline float	CalculateHorizontalDistance();
	inline float	CalculateVerticalDistance();
	inline void		CalculateCameraPosition(const Terrain & terrain);
	inline void		CalculateZoom();
	inline void		CalculatePitch();
	inline void		CalculateAngleAroundPlayer();
		   void		CheckSwitchState();
	
};

