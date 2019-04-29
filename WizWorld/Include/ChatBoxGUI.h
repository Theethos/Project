#ifndef CHAT_BOX_GUI_H
#define CHAT_BOX_GUI_H

#include "GUI.h"
#include "TextField.h"

class ChatBoxGUI : public GUI
{
public:
	ChatBoxGUI(sf::RenderWindow& window, Player& player);
	~ChatBoxGUI();

	// Functions
	void Update(const float &dt);
	void Render(sf::RenderTarget& target);
	inline void Activate() { m_TextField->Activate(); }
	inline void Deactivate() { m_TextField->Deactivate(); }
	inline const bool IsActive() const { return m_TextField->GetActivated(); }

private:
	// Private functions
	void UpdatePosition(const sf::Vector2f &mouse_position);
	void UpdateTextField();
	void InitTextBox();
	void DisplayMessage();
	void HandleCommand();

	float m_Timer;
	bool m_Hovered;
	bool m_Selected;
	TextField* m_TextField;
	std::list<sf::Text> m_TextBox;
};

#endif // !CHAT_BOX_GUI_H
