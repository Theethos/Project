#include "Precompiled_Header.h"
#include "../Include/Macros.h"
#include "../Include/MiniMapGUI.h"

using namespace sf;

const float MiniMapGUI::s_MiniMapScale = 0.3;

MiniMapGUI::MiniMapGUI(RenderWindow& window, Player & player, Texture& map_texture) :
GUI(window, player),
m_MapTexture(map_texture)
{
	m_PlayerPosition.setRadius(2);
	m_PlayerPosition.setFillColor(Color::Red);

	m_MapShape.setSize(Vector2f(m_MapTexture.getSize()));
	m_MapShape.setTexture(&m_MapTexture);
	m_MapShape.setScale(s_MiniMapScale, s_MiniMapScale);

	m_GlobalShape.setSize(Vector2f(m_MapShape.getSize().x * s_MiniMapScale, m_MapShape.getSize().y * s_MiniMapScale) 
						+ Vector2f(m_Window.getSize().x * 0.01, m_Window.getSize().x * 0.01));
	m_GlobalShape.setFillColor(m_GlobalColor);

	m_GlobalShape.setPosition(Vector2f(m_Window.getSize().x - m_GlobalShape.getSize().x, m_Window.getPosition().y));
	m_MapShape.setPosition(m_GlobalShape.getPosition() + Vector2f(m_GlobalShape.getSize().x / 2 - m_MapShape.getSize().x * s_MiniMapScale / 2,
		m_GlobalShape.getSize().y / 2 - m_MapShape.getSize().y * s_MiniMapScale / 2));
	m_MapShape.setTextureRect(IntRect(0, 0, m_MapShape.getSize().x, m_MapShape.getSize().y));
}

MiniMapGUI::~MiniMapGUI()
{
}

void MiniMapGUI::Update(const float & dt)
{
	if (m_Visible)
	{
		if (!Joystick::isConnected(0) && (!GUI::s_Token || m_Move))
			Move();

		if (m_MapTexture.getSize().x > m_MapShape.getSize().x || m_MapTexture.getSize().y > m_MapShape.getSize().y)
			SetTexture(m_MapTexture);

		UpdatePlayerPosition();
	}
}

void MiniMapGUI::Render(RenderTarget& target)
{
	if (m_Visible)
	{
		target.draw(m_GlobalShape);
		target.draw(m_MapShape);
		target.draw(m_PlayerPosition);
	}
}

void MiniMapGUI::SetTexture(Texture& texture)
{
	if (&m_MapTexture != &texture)
	{
		m_MapTexture = texture; 
		m_MapShape.setTexture(&m_MapTexture);
	}
	
	m_MapShape.setTextureRect(IntRect((m_Player.GetSprite().getPosition().x / m_Player.GetSprite().getScale().x - m_MapShape.getSize().x / 2),
									  (m_Player.GetSprite().getPosition().y / m_Player.GetSprite().getScale().y - m_MapShape.getSize().y / 2),
									   m_MapShape.getTextureRect().width,
									   m_MapShape.getTextureRect().height));

}

void MiniMapGUI::UpdatePosition(const Vector2f & mouse_position)
{
	m_GlobalShape.setPosition(mouse_position);
	m_MapShape.setPosition(m_GlobalShape.getPosition() + Vector2f(m_GlobalShape.getSize().x / 2 - m_MapShape.getSize().x * s_MiniMapScale / 2,
						   m_GlobalShape.getSize().y / 2 - m_MapShape.getSize().y * s_MiniMapScale / 2));
}

void MiniMapGUI::UpdatePlayerPosition()
{
	// If the texture is bigger than the shape, the player is always on center of the minimap, and it is the minimap that moves
	if (m_MapTexture.getSize().x > m_MapShape.getSize().x || m_MapTexture.getSize().y > m_MapShape.getSize().y)
		m_PlayerPosition.setPosition(m_GlobalShape.getPosition() + Vector2f(m_GlobalShape.getSize().x / 2, m_GlobalShape.getSize().y / 2));
	// Else, the minimap is fixed and the player moves on it
	else
		m_PlayerPosition.setPosition(m_MapShape.getPosition() + 
						   Vector2f((m_Player.GetSprite().getPosition().x / m_Player.GetSprite().getScale().x) * s_MiniMapScale,
									(m_Player.GetSprite().getPosition().y / m_Player.GetSprite().getScale().y) * s_MiniMapScale));
}
