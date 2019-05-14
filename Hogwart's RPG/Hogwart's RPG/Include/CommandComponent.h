#ifndef COMMAND_COMPONENT_H
#define COMMAND_COMPONENT_H

class ChatBoxGUI;

class CommandComponent
{
public:
	CommandComponent(ChatBoxGUI& chat_box);
	~CommandComponent();

	void HandleCommand();
private:
	ChatBoxGUI& m_ChatBox;
};

#endif // !COMMAND_COMPONENT_H
