#include "Precompiled_Header.h"
#include "../Include/Macros.h"
#include "../Include/ChatBoxGUI.h"

ChatBoxGUI::ChatBoxGUI(sf::RenderWindow &window, Player &player) :
GUI(window, player),
_textField(nullptr),
_hovered(false),
_selected(false)
{
	_globalShape.setSize(sf::Vector2f(_window.getSize().x * 0.25, _window.getSize().y * 0.25));
	_globalShape.setPosition(_window.getPosition().x, _window.getPosition().y + _window.getSize().y - _globalShape.getSize().y);
	_globalShape.setFillColor(_globalColor);

	_textField = new TextField(_globalShape.getPosition().x + _globalShape.getSize().x * 0.05,
							   _globalShape.getPosition().y + _globalShape.getSize().y * 0.80,
							   _globalShape.getSize().x * 0.90, _globalShape.getSize().y * 0.15,
							   "Speak your mind", &_font,_globalColor, sf::Color(0, 0, 0, 50), _globalColor, 0.01 * _window.getSize().x, &_window);
	_textField->setMaxSize(50);

	InitTextBox();
}

ChatBoxGUI::~ChatBoxGUI()
{
	delete _textField;
}

void ChatBoxGUI::Update(const float & dt)
{
	if (_visible)
	{
		if (_globalShape.getGlobalBounds().contains(sf::Vector2f(sf::Mouse::getPosition())) || _textField->getActivated())
			_hovered = true;
		else if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
		{
			_selected = false;
			_hovered = false;
		}
		else
			_hovered = false;

		UpdateTextField();

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Enter) && _textField->getTextEntered() != "")
		{
			DisplayMessage();
			_textField->setTextEntered("");
			_selected = true;
			Activate();
		}

		// Check Drag&Drop
		if (!sf::Joystick::isConnected(0) && (!GUI::_token || _move))
			Move();
	}
}

void ChatBoxGUI::Render(sf::RenderTarget * target)
{
	if (_visible)
	{
		if (!target)
			target = &_window;

		target->draw(_globalShape);

		_hovered || _selected ? _textField->setRenderColor(_globalColorText) : _textField->setRenderColor(_globalColor);
		_textField->Render(target);
		
		for (auto &it : _textBox)
		{
			// Admin Message (in Yellow
			_hovered || _selected ? it.setFillColor(it.getString()[0] == '-' && it.getString()[1] == '>' ? _globalColorText : sf::Color::Yellow) : it.setFillColor(_globalColor);
			target->draw(it);
		}
	}
}

void ChatBoxGUI::UpdatePosition(const sf::Vector2f & mousePos)
{
	_globalShape.setPosition(mousePos);
	_textField->setPosition(_globalShape.getPosition().x + _globalShape.getSize().x * 0.05,
							_globalShape.getPosition().y + _globalShape.getSize().y * 0.80);
	sf::Vector2f tmp(_globalShape.getPosition() + sf::Vector2f(_globalShape.getSize().x * 0.05, _globalShape.getSize().y * 0.05));
	for (auto &it : _textBox)
	{
		it.setPosition(tmp);
		tmp.y += _globalShape.getSize().y * 0.10;
	}

}

void ChatBoxGUI::UpdateTextField()
{
	if (_textField->getPressed())
	{
		_textField->Activate();
		_textField->setPressed(false);
	}
	else if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
		_textField->Deactivate();

	_textField->Update(sf::Vector2f(sf::Mouse::getPosition()));
}

void ChatBoxGUI::InitTextBox()
{
	sf::Vector2f textPosition(_globalShape.getPosition() + sf::Vector2f(_globalShape.getSize().x * 0.05, _globalShape.getSize().y * 0.05));
	std::string text;
	std::ifstream config_file("../External/Config/Text/Welcome.cfg");
	if (config_file.is_open())
	{
		while (std::getline(config_file, text, '\n'))
		{
			if (text == "_") text = "";
			sf::Text newText(text, _font, 0.01 * _window.getSize().x);
			_textBox.push_back(newText);
			_textBox.back().setPosition(textPosition);
			_textBox.back().setFillColor(sf::Color::Yellow);
			textPosition.y += _globalShape.getSize().y * 0.10;
		}
	}
}

void ChatBoxGUI::DisplayMessage()
{
	if (_textField->getTextEntered()[0] == '/')
		HandleCommand();
	else
	{
		// "Push" every message to the one on top of it
		auto it = _textBox.begin();
		auto next = ++_textBox.begin();
		while (next != _textBox.end())
		{
			(it++)->setString((next++)->getString());
		}
		_textBox.back().setString("-> " + _textField->getTextEntered());
	}
}

void ChatBoxGUI::HandleCommand()
{
	if (_textField->getTextEntered() == "/clear")
	{
		for (auto &it : _textBox)
		{
			it.setString("");
		}
	}

	_textField->setTextEntered("");
}
