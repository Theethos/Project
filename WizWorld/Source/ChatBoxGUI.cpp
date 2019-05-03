#include "Precompiled_Header.h"
#include "../Include/Macros.h"
#include "../Include/ChatBoxGUI.h"

using namespace sf;

ChatBoxGUI::ChatBoxGUI(RenderWindow& window, Player& player) :
GUI(window, player),
m_CommandHandler(*this),
m_TextField(nullptr),
m_Hovered(false),
m_Selected(false),
m_Quit(false)
{
	m_GlobalShape.setSize(Vector2f(m_Window.getSize().x * 0.25, m_Window.getSize().y * 0.25));
	m_GlobalShape.setPosition(m_Window.getPosition().x, m_Window.getPosition().y + m_Window.getSize().y - m_GlobalShape.getSize().y);
	m_GlobalShape.setOutlineThickness(1);
	m_GlobalShape.setOutlineColor(Color::Black);
	m_GlobalShape.setFillColor(m_GlobalColor);

	m_TextField = new TextField(m_Window, m_Font, m_GlobalShape.getPosition().x + m_GlobalShape.getSize().x * 0.05,
							    m_GlobalShape.getPosition().y + m_GlobalShape.getSize().y * 0.80,
							    m_GlobalShape.getSize().x * 0.90, m_GlobalShape.getSize().y * 0.15,
							    "", m_GlobalColor + Color(0, 0, 0, 60), Color(0, 0, 0, 50), m_GlobalColor,
								0.01 * m_Window.getSize().x);
	m_TextField->SetMaxSize(50);
	InitTextBox();
	InitKeysPressed();

	m_Field.setSize(m_TextField->GetSize());
	m_Field.setPosition(m_TextField->GetPosition());
	m_Field.setFillColor(m_GlobalColor);

	m_PreviousMessages.first = 0;

	m_Shape = &m_GlobalShape;
}

ChatBoxGUI::~ChatBoxGUI()
{
	delete m_TextField;
}

void ChatBoxGUI::Update(const float & dt)
{
	if (m_Visible)
	{
		if (Keyboard::isKeyPressed(Keyboard::Escape) && m_TextField->GetActivated())
			m_Quit = true;
		else if (m_Quit)
		{
			Deactivate();
			m_Quit = false;
		}
		else if (m_TextField->GetHovered() || m_TextField->GetActivated())
			m_Hovered = true;
		else if (Mouse::isButtonPressed(Mouse::Button::Left) || (m_Selected && (m_Timer += dt) && m_Timer >= 3))
		{
			m_Selected = false;
			m_Hovered = false;
		}
		else
			m_Hovered = false;


		if (Keyboard::isKeyPressed(Keyboard::Enter) && m_TextField->GetTextEntered() != "")
		{
			DisplayMessage();
			m_Selected = true;
			m_Timer = 0;
			m_PreviousMessages.first = std::max(static_cast<int>(m_PreviousMessages.second.size() - 1), 0);
			Deactivate();
		}

		HandleInput();

		UpdateTextField();

		// Check Drag&Drop
		if (!Joystick::isConnected(0) && (!GUI::s_Token || m_Move))
			Move<RectangleShape>();
	}
}

void ChatBoxGUI::Render(RenderTarget& target)
{
	if (m_Visible)
	{
		if (m_Hovered || m_Selected)
		{
			target.draw(m_GlobalShape);
			m_TextField->SetRenderColor(m_GlobalTextColor);
			m_Field.setFillColor(Color(0, 0, 0, 188));
			for (auto &it : m_TextBox)
			{
																						// Admin's Messages (without '->') are in yellow
				it.setFillColor(it.getString()[0] == '-' && it.getString()[1] == '>' ? m_GlobalTextColor : Color::Yellow);
				target.draw(it);
			}
		}
		else
		{
			m_TextField->SetRenderColor(m_GlobalColor);
			m_Field.setFillColor(m_GlobalColor);
		}

		if (!m_Selected && !m_Hovered)
			target.draw(m_Field);
		m_TextField->Render(target);
	}
}

void ChatBoxGUI::UpdatePosition(const Vector2f & mouse_position)
{
	m_Shape->setPosition(mouse_position);
	m_GlobalShape.setPosition(m_Shape->getPosition());
	m_TextField->SetPosition(m_GlobalShape.getPosition().x + m_GlobalShape.getSize().x * 0.05,
							m_GlobalShape.getPosition().y + m_GlobalShape.getSize().y * 0.80);
	m_Field.setPosition(m_TextField->GetPosition());
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

	m_TextField->Update(m_Window.mapPixelToCoords(Mouse::getPosition(m_Window)));
}

void ChatBoxGUI::UpdatePreviousMessages()
{
	if (m_PreviousMessages.second.size() == 6 && m_PreviousMessages.second.back() != m_TextField->GetTextEnteredConst() && m_TextField->GetTextEnteredConst() != "")
	{
		
		for (unsigned i = 0; i < m_PreviousMessages.second.size() - 1; ++i)
			m_PreviousMessages.second[i] = m_PreviousMessages.second[i + 1];
		m_PreviousMessages.second[m_PreviousMessages.second.size() - 1] = m_TextField->GetTextEnteredConst();
	}	
	else if (m_PreviousMessages.second.size() && m_PreviousMessages.second.back() != m_TextField->GetTextEnteredConst() && m_TextField->GetTextEnteredConst() != "")
			m_PreviousMessages.second.push_back(m_TextField->GetTextEnteredConst());
	else 
		m_PreviousMessages.second.push_back(m_TextField->GetTextEnteredConst());
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

void ChatBoxGUI::InitKeysPressed()
{
	m_KeysPressed["UP"] = false;
	m_KeysPressed["DOWN"] = false;
}

void ChatBoxGUI::DisplayMessage()
{
	UpdatePreviousMessages();
	
	if (m_TextField->GetTextEntered()[0] == '/')
		m_CommandHandler.HandleCommand();
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

	m_TextField->SetTextEntered("");
}

void ChatBoxGUI::HandleInput()
{
	// The booleens simulate a key released event
	if (Keyboard::isKeyPressed(Keyboard::Key::Up))
		m_KeysPressed["UP"] = true;
	else if (Keyboard::isKeyPressed(Keyboard::Key::Down))
		m_KeysPressed["DOWN"] = true;
	else if (m_KeysPressed["UP"])
	{
		m_KeysPressed["UP"] = false;
		if (m_PreviousMessages.second.size())
		{
			try
			{
				m_TextField->SetTextEntered(m_PreviousMessages.second[m_PreviousMessages.first]);
			}
			catch (...)
			{
				m_TextField->SetTextEntered("");
			}
			if (m_PreviousMessages.first > 0)
				--m_PreviousMessages.first;			
		}
	}
	else if (m_KeysPressed["DOWN"])
	{
		m_KeysPressed["DOWN"] = false;
		if (m_PreviousMessages.second.size())
		{
			try
			{
				m_TextField->SetTextEntered(m_PreviousMessages.second[m_PreviousMessages.first]);
			}
			catch (...)
			{
				m_TextField->SetTextEntered("");
			}
			if (m_PreviousMessages.first < m_PreviousMessages.second.size() - 1)
				++m_PreviousMessages.first;
		}
	}

}
