#include "../Include/MenuState.h"

#include <cstdlib>
#include <string>

/*
 * ==================================================
 * ================= Class MenuState ================
 * ==================================================
 */

MenuState::MenuState(sf::RenderWindow *window, std::map < std::string, int> *keys, std::stack<State*>* states, std::string configFile) 
		: State(window, keys, states), m_numberOfButtons(0), m_configFile(configFile)
{
	initializeFonts();
	initializeTitle();
	initializeButtons();

	m_background.setSize(sf::Vector2f(m_window->getSize()));

	/* Loads the background's image depending on the size of the window */
	if (m_backgroundTexture.loadFromFile("../External/Images/Background/"+std::to_string(m_window->getSize().x)+"_"+ std::to_string(m_window->getSize().y)+".png"))
		m_background.setTexture(&m_backgroundTexture);
	/* File does not exist */
	else
	{
		m_background.setFillColor(sf::Color::Black);
	}
}

MenuState::~MenuState()
{
	
	for (auto &it : m_buttons)
	{
		delete it.second;
	}
}

void MenuState::handleInput(const double &dt)
{}

void MenuState::update(const double& dt)
{
	updateMousePositions();
	
	handleInput(dt);
	
	updateButtons();
}

void MenuState::updateButtons()
{
	sf::Clock time;
	float u = 0.0;
	for (auto &it : m_buttons)
	{
		it.second->update(m_mousePosView);
		if (it.second->getPressed())
		{
			/* Main Menu */
			if (it.first == "PLAY")
			{
				m_states->push(new GameState(m_window, m_keys, m_states));
			}
			else if (it.first == "QUIT")
			{
				m_window->close();
			}
			/* Pause Menu */
			else if (it.first == "RESUME")
			{
				m_quit = true;
			}
			else if (it.first == "MAIN_MENU")
			{
				m_states->push(new MenuState(m_window, m_keys, m_states, "../External/Config/main_menu_buttons.cfg"));
			}
			else if (it.first == "SETTINGS")
			{
				if (m_window->getSize() == sf::Vector2u(1280, 720))
					m_window->setSize(sf::Vector2u(1920, 1080));
				else if (m_window->getSize() == sf::Vector2u(1920, 1080))
					m_window->setSize(sf::Vector2u(1600, 900));
				else
					m_window->setSize(sf::Vector2u(1280, 720));
			}
		}
	}
}

void MenuState::render(sf::RenderTarget* target)
{
	if (!target)
		target = m_window;

	target->draw(m_background);
	target->draw(m_title);

	renderButtons(target);
}

void MenuState::renderButtons(sf::RenderTarget * target)
{
	for (auto &it : m_buttons)
	{
		it.second->render(target);
	}
}

void MenuState::initializeFonts()
{
	if (!m_font.loadFromFile("../External/Fonts/harryp__.ttf"))
	{
		throw("Error in 'MenuState' : Could not load font");
	}
}
/* Initializes @member[buttons] with the parameters in the files "@member[configFile]"
   Format :
		*** First line for title ***
		x y w h "Text" r1 g1 b1 r2 b2 g2 r3 g3 b3 rText gText bText textSize 
		* x y w h in percentage of the window size;
*/
void MenuState::initializeButtons()
{
	float x_window = m_window->getSize().x, y_window = m_window->getSize().y;

	std::ifstream config_file(m_configFile);
	if (config_file.is_open())
	{
		int i = 0;
		/* Action of the button */
		std::string action = "";
		/* Line in the file */
		std::string line = "";
		/* Coordinates and size of the button */
		double x = 0.0, y = 0.0, w = 0.0, h = 0.0;
		/* Text on the button */
		std::string text = "";
		/* Colors of the button */
		int a = 255;
		sf::Color idle_color = sf::Color::White, hover_color = sf::Color::White, active_color = sf::Color::White, text_color = sf::Color::White;
		/* Size of the text on the button */
		float textSize = 12.0;

		/* Skip the first line */
		std::getline(config_file, line, '\n');

		/* For each buttons of this state */
		while(i < m_numberOfButtons)
		{
			/* Get action */
			std::getline(config_file, action, ' ');

			/* Get coordinates*/
			std::getline(config_file, line, ' ');
			x = std::atof(line.c_str())*x_window;

			std::getline(config_file, line, ' ');
			y = std::atof(line.c_str())*y_window;

			/* Get size */
			std::getline(config_file, line, ' ');
			w = std::atof(line.c_str())*x_window;

			std::getline(config_file, line, ' ');
			h = std::atof(line.c_str())*y_window;
			
			/* Get text */
			std::getline(config_file, text, '-');

			/* Get Idle_Color */
			std::getline(config_file, line, ' ');
			idle_color.r = std::atoi(line.c_str());

			std::getline(config_file, line, ' ');
			idle_color.g = std::atoi(line.c_str());

			std::getline(config_file, line, ' ');
			idle_color.b = std::atoi(line.c_str());

			/* Get Hover_Color */
			std::getline(config_file, line, ' ');
			hover_color.r = std::atoi(line.c_str());

			std::getline(config_file, line, ' ');
			hover_color.g = std::atoi(line.c_str());

			std::getline(config_file, line, ' ');
			hover_color.b = std::atoi(line.c_str());

			/* Get Active_Color */
			std::getline(config_file, line, ' ');
			active_color.r = std::atoi(line.c_str());

			std::getline(config_file, line, ' ');
			active_color.g = std::atoi(line.c_str());

			std::getline(config_file, line, ' ');
			active_color.b = std::atoi(line.c_str());

			/* Get Text_Color */
			std::getline(config_file, line, ' ');
			text_color.r = std::atoi(line.c_str());

			std::getline(config_file, line, ' ');
			text_color.g = std::atoi(line.c_str());

			std::getline(config_file, line, ' ');
			text_color.b = std::atoi(line.c_str());

			/* Get Text_size */
			std::getline(config_file, line, '\n');
			textSize = std::atof(line.c_str())*x_window;

			/* Create the button */
			m_buttons[action] = new Button(x, y, w, h, text, &m_font, idle_color, hover_color, active_color, text_color, textSize);
			i++;
		}
	}
	config_file.close();
}
/* Initializes @member[title] with the FIRST line in the files ""@member[configFile]"
   Format :
		x y "Title"- r g b textSize/ <-- end the line with '/'
		*** Other lines ***
		* x y in percentage of the window size
*/
void MenuState::initializeTitle()
{
	float x_window = m_window->getSize().x, y_window = m_window->getSize().y;

	std::ifstream config_file(m_configFile);

	if (config_file.is_open())
	{
		double x, y;
		float text_size;
		std::string title, line = "";
		sf::Color text_color;

		std::getline(config_file, line, ' ');
		m_numberOfButtons = std::atoi(line.c_str());

		std::getline(config_file, line, ' ');
		x = std::atof(line.c_str())*x_window;

		std::getline(config_file, line, ' ');
		y = std::atof(line.c_str())*y_window;

		std::getline(config_file, title, '-');

		std::getline(config_file, line, ' ');
		text_color.r = std::atoi(line.c_str());

		std::getline(config_file, line, ' ');
		text_color.g = std::atoi(line.c_str());

		std::getline(config_file, line, ' ');
		text_color.b = std::atoi(line.c_str());

		std::getline(config_file, line, ' ');
		text_size = std::atof(line.c_str())*x_window;

		m_title.setFont(m_font);
		m_title.setFillColor(text_color);
		m_title.setCharacterSize(text_size);
		m_title.setString(title);
		m_title.setPosition(sf::Vector2f(x, y));
	}
	config_file.close();
}
