#include "Precompiled_Header.h"
#include "../Include/Macros.h"
#include "../Include/State.h"
#include "../Include/MenuState.h"

// Constructor
State::State(sf::RenderWindow* window, std::stack<State*>* states, WhichState state) :
window(window),
quit(false),
mousePosScreen(0, 0),
mousePosWindow(0, 0),
mousePosView(0, 0),
states(states), 
state(state)
{
	if (this->state != WhichState::MENU_STATE)
	{
		if (sf::Joystick::isConnected(0))
		{
			InitControllerKeys();
			InitControllerActions();
		}
		else
		{
			InitKeyboardKeys();
			InitKeyboardActions();
		}
	}

}
// Destructor
State::~State()
{}

// Functions
void State::UpdateMousePositions()
{
	this->mousePosScreen = sf::Mouse::getPosition();
	this->mousePosWindow = sf::Mouse::getPosition(*this->window);
	this->mousePosView = this->window->mapPixelToCoords(this->mousePosWindow);
}
/////////////////////////////////////////////////////////////////////
/// Initializes the key used in the state with the parameters in the file right file
/// Format :
///	Key_Name SFML_Key_Value
/////////////////////////////////////////////////////////////////////
void State::InitKeyboardKeys()
{
	this->keys.clear();

	std::ifstream config_file;
	auto tmp = static_cast<MenuState*>(this);
	switch (this->state)
	{
	case WhichState::GAME_STATE:
		config_file.open("../External/Config/Input/Keyboard/Game/Inputs.cfg");
		break;
	case WhichState::MENU_STATE:
		switch (tmp->getMenuType())
		{
		case Menu::MAIN_MENU:
			config_file.open("../External/Config/Input/Keyboard/Main_Menu/Inputs.cfg");
			break; 
		case Menu::CHARACTER_MENU:
			config_file.open("../External/Config/Input/Keyboard/Character_Menu/Inputs.cfg");
			break;
		case Menu::PAUSE_MENU:
			config_file.open("../External/Config/Input/Keyboard/Pause_Menu/Inputs.cfg");
			break;
		default:
			break;
		}
		break;
	default:
		break;
	}
	if (config_file.is_open())
	{
		std::string key = "";
		int key_value = 0;
		while (config_file >> key >> key_value)
		{
			this->keys[key] = key_value;
		}
		config_file.close();
	}
}

void State::InitControllerKeys()
{
	this->keys.clear();

	sf::Joystick::Identification id = sf::Joystick::getIdentification(0);
	std::string name = static_cast<std::string>(id.name);
	std::string vendorId = std::to_string(id.vendorId);
	std::string productId = std::to_string(id.productId);

	std::ifstream config_file;
	auto tmp = static_cast<MenuState*>(this);

	switch (this->state)
	{
	case WhichState::GAME_STATE:
		config_file.open("../External/Config/Input/Controller/" + name + "_" + vendorId + "_" + productId + "/Game/Inputs.cfg");
		break;
	case WhichState::MENU_STATE:
		switch (tmp->getMenuType())
		{
		case Menu::MAIN_MENU:
			config_file.open("../External/Config/Input/Controller/" + name + "_" + vendorId + "_" + productId + "/Main_Menu/Inputs.cfg");
			break;
		case Menu::CHARACTER_MENU:
			config_file.open("../External/Config/Input/Controller/" + name + "_" + vendorId + "_" + productId + "/Character_Menu/Inputs.cfg");
			break;
		case Menu::PAUSE_MENU:
			config_file.open("../External/Config/Input/Controller/" + name + "_" + vendorId + "_" + productId + "/Pause_Menu/Inputs.cfg");
			break;
		default:
			break;
		}
		break;
	default:
		break;
	}
	if (config_file.is_open())
	{
		std::string key = "";
		int key_value = 0;
		while (config_file >> key >> key_value)
		{
			this->keys[key] = key_value;
		}
		config_file.close();
	}
}
/////////////////////////////////////////////////////////////////////
/// Initializes the map of actions for each key with the parameters in the files "Game/actions.cfg"
/// Format :
///	Action_Name >> Key_Name
/////////////////////////////////////////////////////////////////////
void State::InitKeyboardActions()
{
	this->actions.clear();

	std::ifstream config_file;
	auto tmp = static_cast<MenuState*>(this);
	switch (this->state)
	{
	case WhichState::GAME_STATE:
		config_file.open("../External/Config/Input/Keyboard/Game/Actions.cfg");
		break;
	case WhichState::MENU_STATE:
		switch (tmp->getMenuType())
		{
		case Menu::MAIN_MENU:
			config_file.open("../External/Config/Input/Keyboard/Main_Menu/Actions.cfg");
			break;
		case Menu::CHARACTER_MENU:
			config_file.open("../External/Config/Input/Keyboard/Character_Menu/Actions.cfg");
			break;
		case Menu::PAUSE_MENU:
			config_file.open("../External/Config/Input/Keyboard/Pause_Menu/Actions.cfg");
			break;
		default:
			break;
		}
		break;
	default:
		break;
	}
	if (config_file.is_open())
	{
		std::string action = "";
		std::string key = "";
		while (config_file >> action >> key)
		{
			this->actions[action] = this->keys[key];
		}
		config_file.close();
	}
}

void State::InitControllerActions()
{
	this->actions.clear();

	sf::Joystick::Identification id = sf::Joystick::getIdentification(0);
	std::string name = static_cast<std::string>(id.name);
	std::string vendorId = std::to_string(id.vendorId);
	std::string productId = std::to_string(id.productId);

	std::ifstream config_file;
	auto tmp = static_cast<MenuState*>(this);
	switch (this->state)
	{
	case WhichState::GAME_STATE:
		config_file.open("../External/Config/Input/Controller/" + name + "_" + vendorId + "_" + productId + "/Game/Actions.cfg");
		break;
	case WhichState::MENU_STATE:
		switch (tmp->getMenuType())
		{
		case Menu::MAIN_MENU:
			config_file.open("../External/Config/Input/Controller/" + name + "_" + vendorId + "_" + productId + "/Main_Menu/Actions.cfg");
			break;
		case Menu::CHARACTER_MENU:
			config_file.open("../External/Config/Input/Controller/" + name + "_" + vendorId + "_" + productId + "/Character_Menu/Actions.cfg");
			break;
		case Menu::PAUSE_MENU:
			config_file.open("../External/Config/Input/Controller/" + name + "_" + vendorId + "_" + productId + "/Pause_Menu/Actions.cfg");
			break;
		default:
			break;
		}
		break;
	default:
		break;
	}
	if (config_file.is_open())
	{
		std::string action = "";
		std::string key = "";
		while (config_file >> action >> key)
		{
			this->actions[action] = this->keys[key];
		}
		config_file.close();
	}
}

// Getters
const bool& State::getQuit() const
{
	return this->quit;
}

const WhichState & State::getState() const
{
	return this->state;
}
