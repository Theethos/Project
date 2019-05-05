#include "Precompiled_Header.h"
#include "../Include/Macros.h"
#include "../Include/EditorGUI.h"

using namespace sf;

EditorGUI::EditorGUI(RenderWindow &window) : 
GUI(window, nullptr),
m_SelectedShape(0)
{
	m_GlobalShape.setSize(sf::Vector2f(m_Window.getSize().x * 0.015, m_Window.getSize().y));
	m_GlobalShape.setPosition(0, 0);
	m_GlobalShape.setFillColor(m_GlobalColor);

	m_Shape = &m_GlobalShape;
}

EditorGUI::~EditorGUI()
{
}

void EditorGUI::Update(const float & dt)
{
	for (int i = 0; i < m_Division.size(); ++i)
	{
		if (m_Division[i].first.getGlobalBounds().contains(m_Window.mapPixelToCoords(Mouse::getPosition(m_Window))))
		{
			if (Mouse::isButtonPressed(Mouse::Button::Left))
				m_SelectedShape = i;
			m_Division[i].first.setFillColor(m_GlobalTextColor);
			m_Division[i].second.setFillColor(m_GlobalColor);
		}
		else
		{
			m_Division[i].first.setFillColor(m_GlobalColor);
			m_Division[i].second.setFillColor(m_GlobalTextColor);
		}
	}
	if (m_SelectedShape >= 0 && m_SelectedShape < m_Division.size())
	{
		m_Division[m_SelectedShape].first.setFillColor(m_GlobalTextColor);
		m_Division[m_SelectedShape].second.setFillColor(m_GlobalColor);
	}
}

void EditorGUI::Render(sf::RenderTarget & target)
{
	target.draw(m_GlobalShape);
	for (auto &it : m_Division)
	{
		target.draw(it.first);
		target.draw(it.second);
	}
}

void EditorGUI::Divide(float number_of_textures)
{
	for (unsigned i = 0; i < number_of_textures; ++i)
	{
		RectangleShape tmp_shape(Vector2f(m_GlobalShape.getSize().x, m_GlobalShape.getSize().y / number_of_textures));
		tmp_shape.setPosition(0, i * m_GlobalShape.getSize().y / number_of_textures);
		tmp_shape.setFillColor(m_GlobalColor);
		tmp_shape.setOutlineColor(Color::White);
		tmp_shape.setOutlineThickness(1);
		ConvexShape tmp_conv(3);
		tmp_conv.setPoint(0, Vector2f(tmp_shape.getSize().x / 4, 5 * tmp_shape.getSize().y / 11));
		tmp_conv.setPoint(1, Vector2f( 3 * tmp_shape.getSize().x / 4, 6 * tmp_shape.getSize().y / 11));
		tmp_conv.setPoint(2, Vector2f(tmp_shape.getSize().x / 4, 7 * tmp_shape.getSize().y / 11));
		tmp_conv.setFillColor(m_GlobalTextColor);
		tmp_conv.setPosition(tmp_shape.getPosition());// +Vector2f(tmp_conv.getGlobalBounds().width / 4.f, tmp_conv.getGlobalBounds().height / 4.f));
		m_Division.push_back(std::make_pair(tmp_shape, tmp_conv));
	}
}

void EditorGUI::UpdatePosition(const sf::Vector2f & mouse_position)
{
}
