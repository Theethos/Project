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
	initializeButtons();
	m_background.setSize(sf::Vector2f(window->getSize()));
	m_background.setFillColor(sf::Color::Black);
}

MainMenuState::~MainMenuState()
{
	for (int i = 0; i < m_buttonText.size(); i++)
	{
		delete m_buttons[i];
	}
	delete[] m_buttons;
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
		m_buttons[i]->update(m_mousePosView);
		if (m_buttons[i]->getPressed())
		{
			if (i == m_buttonText["QUIT"])
				m_quit = true;
			else if (i == m_buttonText["PLAY"])
			{ 
				m_add = new GameState(m_window, m_keys);
			}
		}
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
	/* Get the different actions of buttons (Play, Quit, ... ) */
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
	/* Initializes all buttons */
	m_buttons = new Button*[m_buttonText.size()];

	std::ifstream config_file("../External/Config/main_menu_buttons.cfg");

	if (config_file.is_open())
	{
		/* Line in the file */
		std::string line = "";
		/* Coordinates and size of the button */
		float x = 0.0, y = 0.0, w = 0.0, h = 0.0;
		/* Text on the button */
		std::string text = "";
		/* Colors of the button */
		int r = 0, g = 0, b = 0, a = 255;
		sf::Color idleColor = sf::Color::White, hoverColor = sf::Color::White, activeColor = sf::Color::White, textColor = sf::Color::White;
		/* Size of the text on the button */
		int textSize = 12;

		/* For each buttons of this state */
		for (int i = 0; i < m_buttonText.size(); i++)
		{
			/* Get coordinates*/
			std::getline(config_file, line, ' ');
			x = std::atoi(line.c_str());

			std::getline(config_file, line, ' ');
			y = std::atoi(line.c_str());

			/* Get size */
			std::getline(config_file, line, ' ');
			w = std::atoi(line.c_str());

			std::getline(config_file, line, ' ');
			h = std::atoi(line.c_str());
			
			/* Get text */
			std::getline(config_file, text, ' ');

			/* Get Idle_Color */
			std::getline(config_file, line, ' ');
			idleColor.r = std::atoi(line.c_str());

			std::getline(config_file, line, ' ');
			idleColor.g = std::atoi(line.c_str());

			std::getline(config_file, line, ' ');
			idleColor.b = std::atoi(line.c_str());

			/* Get Hover_Color */
			std::getline(config_file, line, ' ');
			hoverColor.r = std::atoi(line.c_str());

			std::getline(config_file, line, ' ');
			hoverColor.g = std::atoi(line.c_str());

			std::getline(config_file, line, ' ');
			hoverColor.b = std::atoi(line.c_str());

			/* Get Active_Color */
			std::getline(config_file, line, ' ');
			activeColor.r = std::atoi(line.c_str());

			std::getline(config_file, line, ' ');
			activeColor.g = std::atoi(line.c_str());

			std::getline(config_file, line, ' ');
			activeColor.b = std::atoi(line.c_str());

			/* Get Text_Color */
			std::getline(config_file, line, ' ');
			textColor.r = std::atoi(line.c_str());

			std::getline(config_file, line, ' ');
			textColor.g = std::atoi(line.c_str());

			std::getline(config_file, line, ' ');
			textColor.b = std::atoi(line.c_str());

			/* Get Text_size */
			std::getline(config_file, line, '\n');
			textSize = std::atoi(line.c_str());

			/* Create the button */
			m_buttons[i] = new Button(x, y, w, h, text, &m_font, idleColor, hoverColor, activeColor, textColor, textSize);
		}
	}

	config_file.close();
}