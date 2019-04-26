#include "Precompiled_Header.h"
#include "../Include/Macros.h"
#include "../Include/PlayerGUI.h"

// Constructor
PlayerGUI::PlayerGUI(sf::RenderWindow & window, Player & player, std::string &player_name) :
_window(window),
_player(player)
{
	// Global
	_globalColor = sf::Color(0, 0, 0, 200);
	_globalShape.setSize(sf::Vector2f(_window.getSize().x, _window.getSize().y * 0.10)); // 10% of the window's height
	_globalShape.setPosition(0, _window.getSize().y - _globalShape.getSize().y);
	_globalShape.setFillColor(_globalColor);

	if (!_font.loadFromFile("../External/Fonts/GOTHICB.TTF"))
		std::cerr << "Error while loading font in PlayerGUI. Line " << __LINE__ << std::endl;

	// Health bar
	_healthBar.setSize(sf::Vector2f(_window.getSize().x * 0.15, _window.getSize().y * 0.03));
	_healthBar.setPosition(_window.getSize().x * 0.01 , _window.getSize().y * 0.91);
	_healthBar.setFillColor(sf::Color::Red);
	_healthPoints.setString("100/100");
	_healthPoints.setCharacterSize(25);
	_healthPoints.setFont(_font);
	_healthPoints.setFillColor(sf::Color::Black);
	_healthPoints.setPosition(_healthBar.getPosition() + sf::Vector2f((_healthBar.getSize().x - _healthPoints.getGlobalBounds().width) / 2, 0));

	// Exp bar
	_expBar.setSize(_healthBar.getSize());
	_expBar.setPosition(_window.getSize().x * 0.01, _window.getSize().y * 0.955);
	_expBar.setFillColor(sf::Color::Green);
	_expPoints.setString("0/150");
	_expPoints.setCharacterSize(25);
	_expPoints.setFont(_font);
	_expPoints.setFillColor(sf::Color::Black);
	_expPoints.setPosition(_expBar.getPosition() + sf::Vector2f((_expBar.getSize().x - _expPoints.getGlobalBounds().width) / 2, 0));

	// Infos
	_pseudo.setString(player_name);
	_pseudo.setCharacterSize(25);
	_pseudo.setPosition(_healthBar.getPosition() + sf::Vector2f(_healthBar.getSize().x *1.05 , 0));
	_pseudo.setFont(_font);
	_pseudo.setFillColor(sf::Color::White);
	
	_level.setString("Level 1");
	_level.setCharacterSize(25);
	_level.setPosition(_expBar.getPosition() + sf::Vector2f(_expBar.getSize().x *1.05, 0));
	_level.setFont(_font);
	_level.setFillColor(sf::Color::White);
}
// Destructor
PlayerGUI::~PlayerGUI()
{}

// Functions
void PlayerGUI::Update(const float & dt)
{
	std::string currentXp = std::to_string(_player.getStatistics().getCurrentLevelExp());
	std::string nextXp = std::to_string(_player.getStatistics().getNextLevelExp());
	_expPoints.setString(currentXp + "/" + nextXp);

	std::string currentHp = std::to_string(_player.getStatistics().getCurrentHP());
	std::string maxHp = std::to_string(_player.getStatistics().getMaxHP());
	_healthPoints.setString(currentHp + "/" + maxHp);

	std::string level = std::to_string(_player.getStatistics().getLevel());
	_level.setString("Level " + level);
}

void PlayerGUI::Render(sf::RenderTarget * target)
{
	target->draw(_globalShape);
	target->draw(_healthBar);
	target->draw(_expBar);
	target->draw(_pseudo);
	target->draw(_level);
	target->draw(_expPoints);
	target->draw(_healthPoints);
}
