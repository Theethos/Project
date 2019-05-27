#pragma once

class Camera
{
public:
	Camera();
	~Camera();

	void Move();
	
	inline const glm::vec3 GetPosition() const { return m_Position; }
	inline const float GetPitch() const { return m_Pitch; }
	inline const float GetYaw() const { return m_Yaw; }
	inline const float GetRoll() const { return m_Roll; }

private:
	glm::vec3 m_Position;
	double m_Pitch, m_Yaw, m_Roll;
};

