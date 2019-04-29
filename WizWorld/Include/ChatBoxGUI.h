#ifndef CHAT_BOX_GUI_H
#define CHAT_BOX_GUI_H

#include "GUI.h"
#include "TextField.h"

class ChatBoxGUI : public GUI
{
public:
	ChatBoxGUI(sf::RenderWindow &window, Player &player);
	~ChatBoxGUI();

	// Functions
	void Update(const float &dt);
	void Render(sf::RenderTarget *target);
	inline void Activate() { _textField->Activate(); }
	inline void Deactivate() { _textField->Deactivate(); }
	inline const bool IsActive() const { return _textField->getActivated(); }

private:
	// Private functions
	void UpdatePosition(const sf::Vector2f &mousePos);
	void UpdateTextField();
	void InitTextBox();
	void DisplayMessage();
	void HandleCommand();

	bool _hovered;
	bool _selected;
	TextField* _textField;
	std::list<sf::Text> _textBox;
};

#endif // !CHAT_BOX_GUI_H
