#include "Precompiled_Header.h"
#include "../Include/Macros.h"
#include "../Include/GUI.h"

// Static variables;
bool GUI::_token = false;
std::list<GUI*> GUI::_instances;

// Constructor
GUI::GUI(sf::RenderWindow &window, Player &player) :
_window(window),
_player(player),
_visible(true),
_move(false),
_offset(0, 0)
{
	if (!_font.loadFromFile("../External/Fonts/GOTHICB.TTF"))
		std::cerr << "Error while loading font in PlayerGUI. Line " << __LINE__ << std::endl;

	_globalColor = sf::Color(0, 0, 0, 128);
	_globalColorText = sf::Color(sf::Color::White);
	_globalShape.setOutlineThickness(1);
	_globalShape.setOutlineColor(sf::Color::Black);

	// Add the new GUI element to the vector that store every instance
	// It is used to check for collision between instance
	GUI::_instances.push_back(this);
}
// Destructor
GUI::~GUI()
{
	_instances.remove(this);
}

// Function
void GUI::Move()
{
	// Move the GUI in Drag&Drop
	sf::Vector2f mousePos(sf::Mouse::getPosition());
	if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) && _move)
	{
		
		_window.setMouseCursorVisible(false);
		mousePos -= _offset;
		sf::Vector2f window_size(_window.getSize());
		
		if (mousePos.x < 0)
			mousePos.x = 0;
		else if (mousePos.x > window_size.x - _globalShape.getSize().x)
			mousePos.x = window_size.x - _globalShape.getSize().x;
		if (mousePos.y < 0)
			mousePos.y = 0;
		else if (mousePos.y > window_size.y - _globalShape.getSize().y)
			mousePos.y = window_size.y - _globalShape.getSize().y;
		
		// Update positions with the virtual function
		UpdatePosition(mousePos);
	}
	else if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) && _globalShape.getGlobalBounds().contains(mousePos))
	{
		GUI::_token = true;
		_move = true;
		_window.setMouseCursorVisible(false);
		_offset = sf::Vector2f(mousePos - _globalShape.getPosition());
	}
	else
	{
		// Checking for collision between instances
		if (_move)
		{
			for (auto &it : GUI::_instances)
			{
				if (it != this)
				{
					if (it->_globalShape.getGlobalBounds().intersects(_globalShape.getGlobalBounds()))
					{
						UpdatePosition(getNewPosition(it->_globalShape.getGlobalBounds()));
					}
				}
			}
		}
		_move = false;
		_window.setMouseCursorVisible(true);
		GUI::_token = false;
	}
}

// Private Function
const sf::Vector2f GUI::getNewPosition(const sf::FloatRect & intersect) const
{
	// Calculate the minimum offset of the intersection
	float offset_top = std::abs(_globalShape.getPosition().y + _globalShape.getSize().y - intersect.top);
	float offset_left = std::abs(_globalShape.getPosition().x + _globalShape.getSize().x - intersect.left);
	float offset_bottom = std::abs((_globalShape.getPosition().y) - (intersect.top + intersect.height));
	float offset_right = std::abs((_globalShape.getPosition().x) - (intersect.left + intersect.width));

	float min = std::min(offset_bottom, std::min(offset_left, std::min(offset_right, offset_top)));

	sf::Vector2f newPosition(_globalShape.getPosition());

	// And then calculate the new position of the GUI
	if (min == offset_bottom)
	{
		if (intersect.top + intersect.height > _window.getPosition().y + _window.getSize().y - _globalShape.getSize().y)
			newPosition.y = intersect.top - _globalShape.getSize().y;
		else
			newPosition.y = intersect.top + intersect.height;
	}
	else if (min == offset_top)
	{
		if (intersect.top - _globalShape.getSize().y < 0)
			newPosition.y = intersect.top + intersect.height;
		else
			newPosition.y = intersect.top - _globalShape.getSize().y;
	}
	else if (min == offset_right)
	{
		if (intersect.left + intersect.width > _window.getPosition().x + _window.getSize().x - _globalShape.getSize().x)
			newPosition.x = intersect.left - _globalShape.getSize().x;
		else
			newPosition.x = intersect.left + intersect.width;
	}
	else if (min == offset_left)
	{
		if (intersect.left - _globalShape.getSize().x < 0)
			newPosition.x = intersect.left + intersect.width;
		else
			newPosition.x = intersect.left - _globalShape.getSize().x;
	}

	return newPosition;
}
