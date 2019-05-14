#include "Precompiled_Header.h"
#include "../Include/Macros.h"
#include "../Include/PlayerGUI.h"

using namespace sf;

// Constructor
PlayerGUI::PlayerGUI(RenderWindow& window, Player *player, const std::string& player_name) :
GUI(window, player)
{
	// Needed initialisation
	m_PlayerLevel.first.setRadius(m_Window.getSize().x * 0.015); 
	m_PlayerName.setString(player_name);
	m_PlayerName.setCharacterSize(25 * m_Window.getSize().y / 1080);
	m_PlayerName.setFont(m_Font);

	// Global
	// 15% of the m_Window's width and 10% of the m_Window's height by default
	m_GlobalShape.setSize(Vector2f(m_Window.getSize().x * 0.11 + std::max(m_PlayerName.getGlobalBounds().width, m_PlayerLevel.first.getRadius() * 2),
	m_Window.getSize().y * 0.11));
	m_GlobalShape.setPosition(0, 0);
	m_GlobalShape.setOutlineThickness(1);
	m_GlobalShape.setOutlineColor(Color::Black);
	m_GlobalShape.setFillColor(m_GlobalColor);

	// Infos
	m_PlayerName.setPosition(m_GlobalShape.getPosition().x + m_GlobalShape.getSize().x * 0.01, m_GlobalShape.getPosition().y + m_GlobalShape.getSize().y * 0.1);
	m_PlayerName.setFillColor(m_GlobalTextColor);
	
	m_PlayerLevel.first.setFillColor(m_GlobalColor);
	m_PlayerLevel.first.setOutlineColor(m_GlobalTextColor);
	m_PlayerLevel.first.setOutlineThickness(2);
	if (m_PlayerName.getGlobalBounds().width > m_PlayerLevel.first.getRadius() * 2)
		m_PlayerLevel.first.setPosition(m_PlayerName.getPosition() + Vector2f(m_PlayerName.getGlobalBounds().width / 2 - m_PlayerLevel.first.getRadius(),
		m_PlayerName.getGlobalBounds().height + m_PlayerLevel.first.getRadius() / 2));
	else
		m_PlayerLevel.first.setPosition(m_PlayerName.getPosition() + Vector2f(0, m_PlayerName.getGlobalBounds().height + m_PlayerLevel.first.getRadius() / 2));
	m_PlayerLevel.second.setString("1");
	m_PlayerLevel.second.setCharacterSize(25 * m_Window.getSize().y / 1080);
	m_PlayerLevel.second.setFont(m_Font);
	m_PlayerLevel.second.setFillColor(m_GlobalTextColor);
	m_PlayerLevel.second.setPosition(m_PlayerLevel.first.getPosition() + Vector2f((m_PlayerLevel.first.getRadius() + m_PlayerLevel.second.getGlobalBounds().width) / 2.f , m_PlayerLevel.first.getRadius() / 2.f));

	
	// Health bar
	m_HPBar.first.setSize(Vector2f(m_Window.getSize().x * 0.10, m_Window.getSize().y * 0.02));
	m_HPBar.first.setPosition(m_PlayerName.getPosition() + Vector2f(std::max(m_PlayerName.getGlobalBounds().width, m_PlayerLevel.first.getRadius() * 2) + m_Window.getSize().y * 0.01, 0));
	m_HPBar.first.setFillColor(Color::Red);
	m_HPBar.second.setSize(m_HPBar.first.getSize());
	m_HPBar.second.setPosition(m_HPBar.first.getPosition());
	m_HPBar.second.setOutlineColor(m_GlobalTextColor);
	m_HPBar.second.setOutlineThickness(1);
	m_HPBar.second.setFillColor(Color::Transparent);
	m_HPValue.setString("150/150");
	m_HPValue.setCharacterSize(20 * m_Window.getSize().y / 1080);
	m_HPValue.setFont(m_Font);
	m_HPValue.setFillColor(m_GlobalTextColor);
	m_HPValue.setPosition(m_HPBar.first.getPosition() + Vector2f((m_HPBar.first.getSize().x - m_HPValue.getGlobalBounds().width) / 2, 0));

	// Exp bar
	m_EXPBar.first.setSize(m_HPBar.first.getSize());
	m_EXPBar.first.setPosition(m_HPBar.first.getPosition().x, m_HPBar.first.getPosition().y + m_Window.getSize().y * 0.01 + m_EXPBar.first.getSize().y);
	m_EXPBar.first.setFillColor(Color(50, 205, 50, 255));
	m_EXPBar.second.setSize(m_EXPBar.first.getSize());
	m_EXPBar.second.setPosition(m_EXPBar.first.getPosition());
	m_EXPBar.second.setOutlineColor(m_GlobalTextColor);
	m_EXPBar.second.setOutlineThickness(1);
	m_EXPBar.second.setFillColor(Color::Transparent);
	m_EXPValue.setString("0/150");
	m_EXPValue.setCharacterSize(20 * m_Window.getSize().y / 1080);
	m_EXPValue.setFont(m_Font);
	m_EXPValue.setFillColor(m_GlobalTextColor);
	m_EXPValue.setPosition(m_EXPBar.first.getPosition() + Vector2f((m_EXPBar.first.getSize().x - m_EXPValue.getGlobalBounds().width) / 2, 0));

	// Mana bar
	m_ManaBar.first.setSize(m_EXPBar.first.getSize());
	m_ManaBar.first.setPosition(m_EXPBar.first.getPosition().x, m_EXPBar.first.getPosition().y + m_Window.getSize().y * 0.01 + m_ManaBar.first.getSize().y);
	m_ManaBar.first.setFillColor(Color::Blue);
	m_ManaBar.second.setSize(m_ManaBar.first.getSize());
	m_ManaBar.second.setPosition(m_ManaBar.first.getPosition());
	m_ManaBar.second.setOutlineColor(m_GlobalTextColor);
	m_ManaBar.second.setOutlineThickness(1);
	m_ManaBar.second.setFillColor(Color::Transparent);
	m_ManaValue.setString("150/150");
	m_ManaValue.setCharacterSize(20 * m_Window.getSize().y / 1080);
	m_ManaValue.setFont(m_Font);
	m_ManaValue.setFillColor(m_GlobalTextColor);
	m_ManaValue.setPosition(m_ManaBar.first.getPosition() + Vector2f((m_ManaBar.first.getSize().x - m_ManaValue.getGlobalBounds().width) / 2, 0));	

	m_Shape = &m_GlobalShape;
}
// Destructor
PlayerGUI::~PlayerGUI()
{}

// Functions
void PlayerGUI::Update(const float & dt)
{
	if (m_Visible)
	{
		// Check Drag&Drop
		if (!Joystick::isConnected(0) && (!GUI::s_Token || m_Move))
			Move<RectangleShape>();

		// Update texts' and bars' size
		long long currentXp = m_Player->GetStatistics().GetCurrentLevelExp();
		long long nextXp = m_Player->GetStatistics().GetExpForLevel(m_Player->GetStatistics().GetLevel() + 1);
		float previous_next = m_Player->GetStatistics().GetExpForLevel(m_Player->GetStatistics().GetLevel());
		if (m_Player->GetStatistics().GetLevel() < 50)
			m_EXPBar.first.setSize(Vector2f(m_EXPBar.second.getSize().x * (static_cast<double>(currentXp - previous_next) / static_cast<double>(nextXp - previous_next)), m_EXPBar.second.getSize().y));
		else 
			m_EXPBar.first.setSize(Vector2f(m_EXPBar.second.getSize().x, m_EXPBar.second.getSize().y));
		m_EXPValue.setString(std::to_string(currentXp) + "/" + std::to_string(nextXp));

		long currentHp = m_Player->GetStatistics().GetCurrentHP();
		long maxHp = m_Player->GetStatistics().GetMaxHP();
		m_HPBar.first.setSize(Vector2f(m_HPBar.second.getSize().x * static_cast<double>(currentHp) / static_cast<double>(maxHp), m_HPBar.second.getSize().y));
		
		m_HPValue.setString(std::to_string(currentHp) + "/" + std::to_string(maxHp));

		long currentMana = m_Player->GetStatistics().GetCurrentMana();
		long maxMana = m_Player->GetStatistics().GetMaxMana();
		m_ManaBar.first.setSize(Vector2f(m_ManaBar.second.getSize().x * static_cast<double>(currentMana) / static_cast<double>(maxMana), m_ManaBar.second.getSize().y));
		
		m_ManaValue.setString(std::to_string(currentMana) + "/" + std::to_string(maxMana));

		std::string level = std::to_string(m_Player->GetStatistics().GetLevel());
		m_PlayerLevel.second.setString(level);

		// Update texts' positions
		if (level.size() > 1)
			m_PlayerLevel.second.setPosition(m_PlayerLevel.first.getPosition() + Vector2f(m_PlayerLevel.first.getRadius() / 2.f, m_PlayerLevel.first.getRadius() / 2.f));
		else
			m_PlayerLevel.second.setPosition(m_PlayerLevel.first.getPosition() + Vector2f((m_PlayerLevel.first.getRadius() + m_PlayerLevel.second.getGlobalBounds().width) / 2.f, m_PlayerLevel.first.getRadius() / 2.f));
		m_HPValue.setPosition(m_HPBar.second.getPosition() + Vector2f((m_HPBar.second.getSize().x - m_HPValue.getGlobalBounds().width) / 2, 0));
		m_EXPValue.setPosition(m_EXPBar.second.getPosition() + Vector2f((m_EXPBar.second.getSize().x - m_EXPValue.getGlobalBounds().width) / 2, 0));
		m_ManaValue.setPosition(m_ManaBar.second.getPosition() + Vector2f((m_ManaBar.second.getSize().x - m_ManaValue.getGlobalBounds().width) / 2, 0));
	}
}

void PlayerGUI::Render(RenderTarget& target)
{
	if (m_Visible)
	{
		target.draw(m_GlobalShape);
		target.draw(m_HPBar.first);
		target.draw(m_EXPBar.first);
		target.draw(m_ManaBar.first);
		target.draw(m_HPBar.second);
		target.draw(m_EXPBar.second);
		target.draw(m_ManaBar.second);
		target.draw(m_PlayerLevel.first);
		target.draw(m_PlayerName);
		target.draw(m_PlayerLevel.second);
		target.draw(m_HPValue);
		target.draw(m_EXPValue);
		target.draw(m_ManaValue);
	}
}

void PlayerGUI::UpdatePosition(const Vector2f & mouse_position)
{
	// Update all the position based on the new position of the global shape (Text are updated in Update())
	m_Shape->setPosition(mouse_position);
	m_GlobalShape.setPosition(m_Shape->getPosition());
	m_PlayerName.setPosition(m_GlobalShape.getPosition().x + m_GlobalShape.getSize().x * 0.01, m_GlobalShape.getPosition().y + m_GlobalShape.getSize().y * 0.1);
	if (m_PlayerName.getGlobalBounds().width > m_PlayerLevel.first.getRadius() * 2)
		m_PlayerLevel.first.setPosition(m_PlayerName.getPosition() + Vector2f(m_PlayerName.getGlobalBounds().width / 2 - m_PlayerLevel.first.getRadius(),
		m_PlayerName.getGlobalBounds().height + m_PlayerLevel.first.getRadius() / 2));
	else
		m_PlayerLevel.first.setPosition(m_PlayerName.getPosition() + Vector2f(0, m_PlayerName.getGlobalBounds().height + m_PlayerLevel.first.getRadius() / 2));
	m_HPBar.first.setPosition(m_PlayerName.getPosition() + Vector2f(std::max(m_PlayerName.getGlobalBounds().width, m_PlayerLevel.first.getRadius() * 2) + m_Window.getSize().y * 0.01, 0));
	m_EXPBar.first.setPosition(m_HPBar.first.getPosition().x, m_HPBar.first.getPosition().y + m_Window.getSize().y * 0.01 + m_EXPBar.first.getSize().y);
	m_ManaBar.first.setPosition(m_EXPBar.first.getPosition().x, m_EXPBar.first.getPosition().y + m_Window.getSize().y * 0.01 + m_ManaBar.first.getSize().y);
	m_HPBar.second.setPosition(m_HPBar.first.getPosition());
	m_EXPBar.second.setPosition(m_EXPBar.first.getPosition());
	m_ManaBar.second.setPosition(m_ManaBar.first.getPosition());
}


