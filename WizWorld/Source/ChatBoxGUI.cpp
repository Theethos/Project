#include "Precompiled_Header.h"
#include "../Include/Macros.h"
#include "../Include/ChatBoxGUI.h"

using namespace sf;

ChatBoxGUI::ChatBoxGUI(RenderWindow& window, Player& player) :
GUI(window, player),
m_TextField(nullptr),
m_Hovered(false),
m_Selected(false)
{
	m_GlobalShape.setSize(Vector2f(m_Window.getSize().x * 0.25, m_Window.getSize().y * 0.25));
	m_GlobalShape.setPosition(m_Window.getPosition().x, m_Window.getPosition().y + m_Window.getSize().y - m_GlobalShape.getSize().y);
	m_GlobalShape.setFillColor(m_GlobalColor);

	m_TextField = new TextField(m_Window, m_Font, m_GlobalShape.getPosition().x + m_GlobalShape.getSize().x * 0.05,
							    m_GlobalShape.getPosition().y + m_GlobalShape.getSize().y * 0.80,
							    m_GlobalShape.getSize().x * 0.90, m_GlobalShape.getSize().y * 0.15,
							    "Speak your mind", m_GlobalColor, Color(0, 0, 0, 50), m_GlobalColor, 0.01 * m_Window.getSize().x);
	m_TextField->SetMaxSize(50);
	InitTextBox();
}

ChatBoxGUI::~ChatBoxGUI()
{
	delete m_TextField;
}

void ChatBoxGUI::Update(const float & dt)
{
	if (m_Visible)
	{
		if (m_GlobalShape.getGlobalBounds().contains(Vector2f(Mouse::getPosition())) || m_TextField->GetActivated())
			m_Hovered = true;
		else if (Mouse::isButtonPressed(Mouse::Button::Left) || (m_Selected && (m_Timer += dt) && m_Timer > 2))
		{
			m_Selected = false;
			m_Hovered = false;
		}
		else
			m_Hovered = false;

		UpdateTextField();

		if (Keyboard::isKeyPressed(Keyboard::Key::Enter) && m_TextField->GetTextEntered() != "")
		{
			DisplayMessage();
			m_TextField->SetTextEntered("");
			m_Selected = true;
			m_Timer = 0;
		}

		// Check Drag&Drop
		if (!Joystick::isConnected(0) && (!GUI::s_Token || m_Move))
			Move();
	}
}

void ChatBoxGUI::Render(RenderTarget& target)
{
	if (m_Visible)
	{
		target.draw(m_GlobalShape);

		m_Hovered || m_Selected ? m_TextField->SetRenderColor(m_GlobalTextColor) : m_TextField->SetRenderColor(m_GlobalColor);
		m_TextField->Render(target);
		
		for (auto &it : m_TextBox)
		{
			// Admin Message (in Yellow
			m_Hovered || m_Selected ? it.setFillColor(it.getString()[0] == '-' && it.getString()[1] == '>' ? m_GlobalTextColor : Color::Yellow) : it.setFillColor(m_GlobalColor);
			target.draw(it);
		}
	}
}

void ChatBoxGUI::UpdatePosition(const Vector2f & mouse_position)
{
	m_GlobalShape.setPosition(mouse_position);
	m_TextField->SetPosition(m_GlobalShape.getPosition().x + m_GlobalShape.getSize().x * 0.05,
							m_GlobalShape.getPosition().y + m_GlobalShape.getSize().y * 0.80);
	Vector2f tmp(m_GlobalShape.getPosition() + Vector2f(m_GlobalShape.getSize().x * 0.05, m_GlobalShape.getSize().y * 0.05));
	for (auto &it : m_TextBox)
	{
		it.setPosition(tmp);
		tmp.y += m_GlobalShape.getSize().y * 0.10;
	}

}

void ChatBoxGUI::UpdateTextField()
{
	if (m_TextField->GetPressed())
	{
		m_TextField->Activate();
		m_TextField->SetPressed(false);
	}
	else if (Mouse::isButtonPressed(Mouse::Button::Left))
		m_TextField->Deactivate();

	m_TextField->Update(Vector2f(Mouse::getPosition()));
}

void ChatBoxGUI::InitTextBox()
{
	Vector2f textPosition(m_GlobalShape.getPosition() + Vector2f(m_GlobalShape.getSize().x * 0.05, m_GlobalShape.getSize().y * 0.05));
	std::string text;
	std::ifstream config_file("../External/Config/Text/Welcome.cfg");
	if (config_file.is_open())
	{
		while (std::getline(config_file, text, '\n'))
		{
			if (text == "_") text = "";
			Text newText(text, m_Font, 0.01 * m_Window.getSize().x);
			m_TextBox.push_back(newText);
			m_TextBox.back().setPosition(textPosition);
			m_TextBox.back().setFillColor(Color::Yellow);
			textPosition.y += m_GlobalShape.getSize().y * 0.10;
		}
	}
}

void ChatBoxGUI::DisplayMessage()
{
	if (m_TextField->GetTextEntered()[0] == '/')
		HandleCommand();
	else
	{
		// "Push" every message to the one on top of it
		auto it = m_TextBox.begin();
		auto next = ++m_TextBox.begin();
		while (next != m_TextBox.end())
		{
			(it++)->setString((next++)->getString());
		}
		m_TextBox.back().setString("-> " + m_TextField->GetTextEntered());
	}
}

void ChatBoxGUI::HandleCommand()
{
	if (m_TextField->GetTextEntered() == "/clear")
	{
		for (auto &it : m_TextBox)
		{
			it.setString("");
		}
	}

	m_TextField->SetTextEntered("");
}
