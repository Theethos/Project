#pragma once

#include "Entity.h"
#include "Terrain.h"

class Player : public Entity
{
public:
	Player(const TexturedModel & model, const glm::vec3 & position, const glm::vec3 & rotation, const float & scale);
	~Player();

	void Move(const Terrain & terrain, const double & dt);

	inline bool IsInAir() const { return m_IsInAir; }
private:
	static float Speed, TurnSpeed, JumpPower, Gravity;
	float m_CurrentSpeedForward, m_CurrentSpeedSideway, m_CurrentTurnSpeed, m_UpwardSpeed, m_BaseUpTranslation;
	bool m_IsInAir;
};

