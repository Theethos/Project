#pragma once
class GameGL
{
public:
	GameGL();
	~GameGL();

	void Run();

private:
	sf::RenderWindow m_Window;
	sf::ContextSettings m_Settings;
	sf::Event m_Event;
	bool m_IsRunning;

	// Private functions
	void Initialize();
	void Update();
	void UpdateEvents();
};

