#ifndef CHAT_BOX_GUI_H
#define CHAT_BOX_GUI_H

#include "GUI.h"
#include "TextField.h"
#include "CommandComponent.h"

class ChatBoxGUI : public GUI
{
public:
	ChatBoxGUI(sf::RenderWindow& window, Player *player);
	~ChatBoxGUI();

	// Functions
	void Update(const float &dt);
	void Render(sf::RenderTarget& target);
	inline void Activate() { m_TextField->Activate(); }
	inline void Deactivate() { m_TextField->Deactivate(); }
	inline const bool IsActive() const { return m_TextField->GetActivated(); }
	inline void HandleInput(int input) { m_TextField->HandleInput(input); }

	friend CommandComponent;
private:
	// Redefining GlobalShape
	sf::RectangleShape m_GlobalShape;

	// Private functions
	void UpdatePosition(const sf::Vector2f &mouse_position);
	void UpdateTextField();
	void UpdatePreviousMessages();
	void InitTextBox();
	void InitKeysPressed();
	void DisplayMessage();
	void HandleInput();

	float m_Timer;													// Timer to hide the box when after some time (3secs)
	
	bool m_Hovered;													// Booleen to display the box when the user is hovering it
	bool m_Selected;												//
	bool m_Quit;													// Booleen to wait until the user realeases "Escape" (to close the box)

	TextField* m_TextField;											// Field displayed when the box is active and that recover user's inputs
	sf::RectangleShape m_Field;										// Field displayed when the box is not active
	std::list<sf::Text> m_TextBox;									// Text displayed in the chat box
	std::pair<int, std::vector<std::string>> m_PreviousMessages;		// The 6 last previous messages
	std::map <std::string, bool> m_KeysPressed;

	CommandComponent m_CommandHandler;								// Component that executes the commands of the user
	
};

#endif // !CHAT_BOX_GUI_H
