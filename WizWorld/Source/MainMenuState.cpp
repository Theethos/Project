#include "../Include/MainMenuState.h"

/*
 * ==================================================
 * =============== Class MainMenuState ==============
 * ==================================================
 */

MainMenuState::MainMenuState(sf::RenderWindow *window, std::map < std::string, int> *keys) : State(window, keys)
{
	initializeFonts();
	initializeActions();
	m_background.setSize(sf::Vector2f(window->getSize()));
	m_background.setFillColor(sf::Color::Red);
}

MainMenuState::~MainMenuState()
{

}

void MainMenuState::handleInput(const float &dt)
{
	checkForQuit(dt);
}

void MainMenuState::update(const float& dt)
{
	updateMousePositions();
	handleInput(dt);
	for (int i = 0; i < m_buttonText.size(); i++)
	{
		m_buttons[i]->update((sf::Vector2f)m_mousePosScreen);
	}
}

void MainMenuState::render(sf::RenderTarget* target)
{
	if (!target)
		target = m_window;

	target->draw(m_background);
	for (int i = 0; i < m_buttonText.size(); i++)
	{
		m_buttons[i]->render(target);
	}
}

void MainMenuState::addState(State * state)
{

}
/* Initializes @member[actions] with the parameters in the files "game_actions.cfg"
   Format :
		Action_Name Key_Name
*/
void MainMenuState::initializeActions()
{
	std::ifstream config_file("../External/Config/game_actions.cfg");

	if (config_file.is_open())
	{
		std::string action = "";
		std::string key = "";
		while (config_file >> action >> key)
		{
			m_actions[action] = m_keys->at(key);
		}
	}

	config_file.close();
	m_actions["END_STATE"] = sf::Keyboard::Key::B;

}

void MainMenuState::initializeFonts()
{
	if (!m_font.loadFromFile("../External/Fonts/harryp__.ttf"))
	{
		throw("Error in 'MainMenuState' : Could not load font");
	}
}

void MainMenuState::initializeButtons()
{
	std::ifstream config_file("../External/Config/main_menu_buttons_actions.cfg");

	if (config_file.is_open())
	{
		std::string action = "";
		int value = 0;
		while (config_file >> action >> value)
		{
			m_buttonText[action] = value;
		}
	}

	config_file.close();

	m_buttons = new Button*[m_buttonText.size()];

	config_file.open("../External/Config/main_menu_buttons.cfg");

	if (config_file.is_open())
	{
		float x, y, w, h;
		std::string text;
		unsigned int r = 0, g = 0, b = 0;
		sf::Color idleColor, hoverColor, activeColor, textColor;
		int textSize;

		for (int i = 0; i < m_buttonText.size(); i++)
		{
			config_file >> x >> y >> w >> h >> text;

			config_file >> r >> g >> b;
			idleColor.r = r; idleColor.g = g; idleColor.b = b;

			config_file >> r >> g >> b;
			hoverColor.r = r; hoverColor.g = g; hoverColor.b = b;

			config_file >> r >> g >> b;
			activeColor.r = r; activeColor.g = g; activeColor.b = b;

			config_file >> r >> g >> b >> textSize;
			textColor.r = r; textColor.g = g; textColor.b = b;

			m_buttons[i] = new Button(x, y, w, h, text, &m_font, idleColor, hoverColor, activeColor, textColor, textSize);
		}
	}

	config_file.close();
}