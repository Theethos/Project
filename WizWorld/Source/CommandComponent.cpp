#include "Precompiled_Header.h"
#include "../Include/Macros.h"
#include "../Include/CommandComponent.h"
#include "../Include/ChatBoxGUI.h"

using namespace sf;

CommandComponent::CommandComponent(ChatBoxGUI& chat_box) : 
m_ChatBox(chat_box)
{
}

CommandComponent::~CommandComponent()
{
}

void CommandComponent::HandleCommand()
{
	std::string &text = m_ChatBox.m_TextField->GetTextEntered();
	if (text == "/clear")
		for (auto &it : m_ChatBox.m_TextBox)
			it.setString("");
	else if (text == "/stuck")
		m_ChatBox.m_Player.GetSprite().setPosition(m_ChatBox.m_Window.getSize().x / 2, m_ChatBox.m_Window.getSize().y / 2);
	else if (text.find("/xp ") != std::string::npos)
	{
		text.erase(text.begin(), text.begin() + 4);
		int amount = std::atoll(text.data());
		if (amount > 0)
			m_ChatBox.m_Player.GetStatistics().AddExp(amount);
		else if (amount < 0)
			m_ChatBox.m_Player.GetStatistics().RemoveExp(-amount);
		else
		{
			if (text.find("-level ") != std::string::npos)
			{
				text.erase(text.begin(), text.begin() + 7);
				int level = std::atoi(text.data());
				if (level > 0 && level <= 50)
				{
					m_ChatBox.m_Player.GetStatistics().SetLevel(level);
				}
			}
		}
	}
}
