#pragma once

class Camera
{
public:
	Camera();
	Camera(glm::vec3 eyes, glm::vec3 center,glm::vec3 up);
	~Camera();

	void Move();
	void LookAt();

	inline const float GetSpeed() const { return m_Speed; }
	inline const float GetSensitivty() const { return m_Sensitivity; }
	inline void SetSpeed(const float & speed) { m_Speed = speed; }
	inline void SetSensitivty(const float & sensitivity) { m_Sensitivity = sensitivity; }

private:
	float m_Speed, m_Sensitivity;
	float m_Theta;
	float m_Phi;
	glm::vec3 m_Orientation;
	glm::vec3 m_VerticalAxis;
	glm::vec3 m_Position;
	glm::vec3 m_Target;
	glm::vec3 m_LateralMotion;

	void InitAngles();
	void Orientate();
	void UpdateOrientation();
};

