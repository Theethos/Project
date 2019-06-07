#pragma once

#include "Player.h"

class Camera
{
public:
	Camera(Player & player);
	~Camera();

	void Move(const double & dt);
	
	inline const Player & GetPlayer() const { return m_Player; }
	inline const glm::vec3 GetPosition() const { return m_Position; }
	inline const float GetPitch() const { return m_Pitch; }

private:
	Player & m_Player;
	glm::vec3 m_Position;
	float m_DistanceFromPlayer, m_AngleAroundPlayer, m_Pitch;

	inline float	CalculateHorizontalDistance();
	inline float	CalculateVerticalDistance();
	inline void		CalculateCameraPosition();
	inline void		CalculateZoom();
	inline void		CalculatePitch();
	inline void		CalculateAngleAroundPlayer();
};

