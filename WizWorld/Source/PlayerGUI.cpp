#include "Precompiled_Header.h"
#include "../Include/Macros.h"
#include "../Include/PlayerGUI.h"

// Constructor
PlayerGUI::PlayerGUI(sf::RenderWindow & window, Player & player, std::string &player_name) :
GUI(window, player)
{
	// Needed initialisation
	_levelShape.setRadius(_window.getSize().x * 0.015); 
	_pseudo.setString(player_name);
	_pseudo.setCharacterSize(25);
	_pseudo.setFont(_font);

	// Global
	// 15% of the window's width and 10% of the window's height by default
	_globalShape.setSize(sf::Vector2f(_window.getSize().x * 0.11 + std::max(_pseudo.getGlobalBounds().width, _levelShape.getRadius() * 2),
	_window.getSize().y * 0.11));
	_globalShape.setPosition(_window.getPosition().x, _window.getPosition().y);
	_globalShape.setFillColor(_globalColor);

	// Infos
	_pseudo.setPosition(_globalShape.getPosition().x + _globalShape.getSize().x * 0.01, _globalShape.getPosition().y + _globalShape.getSize().y * 0.1);
	_pseudo.setFillColor(_globalColorText);
	
	_levelShape.setFillColor(_globalColor);
	_levelShape.setOutlineColor(_globalColorText);
	_levelShape.setOutlineThickness(2);
	if (_pseudo.getGlobalBounds().width > _levelShape.getRadius() * 2)
		_levelShape.setPosition(_pseudo.getPosition() + sf::Vector2f(_pseudo.getGlobalBounds().width / 2 - _levelShape.getRadius(),
		_pseudo.getGlobalBounds().height + _levelShape.getRadius() / 2));
	else
		_levelShape.setPosition(_pseudo.getPosition() + sf::Vector2f(0, _pseudo.getGlobalBounds().height + _levelShape.getRadius() / 2));
	_level.setString("1");
	_level.setCharacterSize(25);
	_level.setFont(_font);
	_level.setFillColor(_globalColorText);
	_level.setPosition(_levelShape.getPosition() + sf::Vector2f((_levelShape.getRadius() + _level.getGlobalBounds().width) / 2.f , _levelShape.getRadius() / 2.f));

	
	// Health bar
	_healthBar.setSize(sf::Vector2f(_window.getSize().x * 0.10, _window.getSize().y * 0.02));
	_healthBar.setPosition(_pseudo.getPosition() + sf::Vector2f(std::max(_pseudo.getGlobalBounds().width, _levelShape.getRadius() * 2) + _window.getSize().y * 0.01, 0));
	_healthBar.setFillColor(sf::Color::Red);
	_healthBarFull.setSize(_healthBar.getSize());
	_healthBarFull.setPosition(_healthBar.getPosition());
	_healthBarFull.setOutlineColor(_globalColorText);
	_healthBarFull.setOutlineThickness(1);
	_healthBarFull.setFillColor(sf::Color::Transparent);
	_healthPoints.setString("150/150");
	_healthPoints.setCharacterSize(20);
	_healthPoints.setFont(_font);
	_healthPoints.setFillColor(_globalColorText);
	_healthPoints.setPosition(_healthBar.getPosition() + sf::Vector2f((_healthBar.getSize().x - _healthPoints.getGlobalBounds().width) / 2, 0));

	// Exp bar
	_expBar.setSize(_healthBar.getSize());
	_expBar.setPosition(_healthBar.getPosition().x, _healthBar.getPosition().y + _window.getSize().y * 0.01 + _expBar.getSize().y);
	_expBar.setFillColor(sf::Color(50, 205, 50, 255));
	_expBarFull.setSize(_expBar.getSize());
	_expBarFull.setPosition(_expBar.getPosition());
	_expBarFull.setOutlineColor(_globalColorText);
	_expBarFull.setOutlineThickness(1);
	_expBarFull.setFillColor(sf::Color::Transparent);
	_expPoints.setString("0/150");
	_expPoints.setCharacterSize(20);
	_expPoints.setFont(_font);
	_expPoints.setFillColor(_globalColorText);
	_expPoints.setPosition(_expBar.getPosition() + sf::Vector2f((_expBar.getSize().x - _expPoints.getGlobalBounds().width) / 2, 0));

	// Mana bar
	_manaBar.setSize(_expBar.getSize());
	_manaBar.setPosition(_expBar.getPosition().x, _expBar.getPosition().y + _window.getSize().y * 0.01 + _manaBar.getSize().y);
	_manaBar.setFillColor(sf::Color::Blue);
	_manaBarFull.setSize(_manaBar.getSize());
	_manaBarFull.setPosition(_manaBar.getPosition());
	_manaBarFull.setOutlineColor(_globalColorText);
	_manaBarFull.setOutlineThickness(1);
	_manaBarFull.setFillColor(sf::Color::Transparent);
	_manaPoints.setString("150/150");
	_manaPoints.setCharacterSize(20);
	_manaPoints.setFont(_font);
	_manaPoints.setFillColor(_globalColorText);
	_manaPoints.setPosition(_manaBar.getPosition() + sf::Vector2f((_manaBar.getSize().x - _manaPoints.getGlobalBounds().width) / 2, 0));	
}
// Destructor
PlayerGUI::~PlayerGUI()
{}

// Functions
void PlayerGUI::Update(const float & dt)
{
	if (_visible)
	{
		// Check Drag&Drop
		if (!sf::Joystick::isConnected(0) && (!GUI::_token || _move))
			Move();

		// Update texts' and bars' size
		long long currentXp = _player.getStatistics().getCurrentLevelExp();
		long long nextXp = _player.getStatistics().getNextLevelExp();
		float previous_next = _player.getStatistics().getPreviousNext() == 150 ? 0 : _player.getStatistics().getPreviousNext();
		_expBar.setSize(sf::Vector2f(_expBarFull.getSize().x * static_cast<double>(currentXp - previous_next) / static_cast<double>(nextXp - previous_next), _expBarFull.getSize().y));
		
		_expPoints.setString(std::to_string(currentXp) + "/" + std::to_string(nextXp));

		long currentHp = _player.getStatistics().getCurrentHP();
		long maxHp = _player.getStatistics().getMaxHP();
		_healthBar.setSize(sf::Vector2f(_healthBarFull.getSize().x * static_cast<double>(currentHp) / static_cast<double>(maxHp), _healthBarFull.getSize().y));
		
		_healthPoints.setString(std::to_string(currentHp) + "/" + std::to_string(maxHp));

		long currentMana = _player.getStatistics().getCurrentMana();
		long maxMana = _player.getStatistics().getMaxMana();
		_manaBar.setSize(sf::Vector2f(_manaBarFull.getSize().x * static_cast<double>(currentMana) / static_cast<double>(maxMana), _manaBarFull.getSize().y));
		
		_manaPoints.setString(std::to_string(currentMana) + "/" + std::to_string(maxMana));

		std::string level = std::to_string(_player.getStatistics().getLevel());
		_level.setString(level);

		// Update texts' positions
		if (level.size() > 1)
			_level.setPosition(_levelShape.getPosition() + sf::Vector2f(_levelShape.getRadius() / 2.f, _levelShape.getRadius() / 2.f));
		else
			_level.setPosition(_levelShape.getPosition() + sf::Vector2f((_levelShape.getRadius() + _level.getGlobalBounds().width) / 2.f, _levelShape.getRadius() / 2.f));
		_healthPoints.setPosition(_healthBarFull.getPosition() + sf::Vector2f((_healthBarFull.getSize().x - _healthPoints.getGlobalBounds().width) / 2, 0));
		_expPoints.setPosition(_expBarFull.getPosition() + sf::Vector2f((_expBarFull.getSize().x - _expPoints.getGlobalBounds().width) / 2, 0));
		_manaPoints.setPosition(_manaBarFull.getPosition() + sf::Vector2f((_manaBarFull.getSize().x - _manaPoints.getGlobalBounds().width) / 2, 0));
	}
}

void PlayerGUI::Render(sf::RenderTarget * target)
{
	if (_visible)
	{
		if (!target)
			target = &_window;

		target->draw(_globalShape);
		target->draw(_healthBar);
		target->draw(_expBar);
		target->draw(_manaBar);
		target->draw(_healthBarFull);
		target->draw(_expBarFull);
		target->draw(_manaBarFull);
		target->draw(_levelShape);
		target->draw(_pseudo);
		target->draw(_level);
		target->draw(_healthPoints);
		target->draw(_expPoints);
		target->draw(_manaPoints);
	}
}

void PlayerGUI::UpdatePosition(const sf::Vector2f & mousePos)
{
	// Update all the position based on the new position of the global shape (Text are updated in Update())
	_globalShape.setPosition(mousePos);
	_pseudo.setPosition(_globalShape.getPosition().x + _globalShape.getSize().x * 0.01, _globalShape.getPosition().y + _globalShape.getSize().y * 0.1);
	if (_pseudo.getGlobalBounds().width > _levelShape.getRadius() * 2)
		_levelShape.setPosition(_pseudo.getPosition() + sf::Vector2f(_pseudo.getGlobalBounds().width / 2 - _levelShape.getRadius(),
		_pseudo.getGlobalBounds().height + _levelShape.getRadius() / 2));
	else
		_levelShape.setPosition(_pseudo.getPosition() + sf::Vector2f(0, _pseudo.getGlobalBounds().height + _levelShape.getRadius() / 2));
	_healthBar.setPosition(_pseudo.getPosition() + sf::Vector2f(std::max(_pseudo.getGlobalBounds().width, _levelShape.getRadius() * 2) + _window.getSize().y * 0.01, 0));
	_expBar.setPosition(_healthBar.getPosition().x, _healthBar.getPosition().y + _window.getSize().y * 0.01 + _expBar.getSize().y);
	_manaBar.setPosition(_expBar.getPosition().x, _expBar.getPosition().y + _window.getSize().y * 0.01 + _manaBar.getSize().y);
	_healthBarFull.setPosition(_healthBar.getPosition());
	_expBarFull.setPosition(_expBar.getPosition());
	_manaBarFull.setPosition(_manaBar.getPosition());
}


