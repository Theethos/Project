#include "../Include/MenuState.h"

#include <cstdlib>
#include <string>
#include "../Include/ChooseCharacterState.h"

MenuState::MenuState(sf::RenderWindow *window, std::map < std::string, int> *keys, std::stack<State*>* states, std::string configFile, Menu currentMenu)
	: State(window, keys, states), numberOfButtons(0), configFile(configFile), currentClassButton(nullptr), currentMenu(currentMenu), menuSprite(nullptr)
{
	initFonts();
	initTitle();
	initButtons();

	this->background.setSize(sf::Vector2f(this->window->getSize()));

	/* Loads the background's image depending on the size of the window */
	if (this->backgroundTexture.loadFromFile("../External/Images/Background/"+std::to_string(this->window->getSize().x)+"_"+ std::to_string(this->window->getSize().y)+".png"))
		this->background.setTexture(&this->backgroundTexture);
	/* File does not exist */
	else
	{
		this->background.setFillColor(sf::Color::Black);
	}

	if (currentMenu == Menu::CHARACTER_MENU)
	{
		initSprites();
	}
}

MenuState::~MenuState()
{
	
	for (auto &it : this->buttons)
	{
		delete it.second;
	}
	if (this->menuSprite)
	{
		delete this->menuSprite;
	}
	if (this->currentSpriteAnimation)
	{
		delete this->currentSpriteAnimation;
	}

}

void MenuState::handleInput(const float &dt)
{}

void MenuState::update(const float& dt)
{
	updateMousePositions();
	
	handleInput(dt);
	
	updateButtons();
}

void MenuState::updateButtons()
{
	for (auto &it : this->buttons)
	{
		it.second->update(this->mousePosView);
		if (it.second->getPressed())
		{
			/* Main Menu */
			if (it.first == "PLAY")
			{
				this->states->push(new MenuState(this->window, this->keys, this->states, "../External/Config/choose_character.cfg", Menu::CHARACTER_MENU));
			}
			else if (it.first == "QUIT")
			{
				this->window->close();
			}
			/* Pause Menu */
			else if (it.first == "RESUME")
			{
				this->quit = true;
			}
			else if (it.first == "MAIN_MENU")
			{
				this->states->push(new MenuState(this->window, this->keys, this->states, "../External/Config/main_menu_buttons.cfg", Menu::MAIN_MENU));
			}
			else if (it.first == "SETTINGS")
			{}
			/* Choose Character Menu */
			else if (it.first == "MALE")
			{
				it.second->activate();
				this->buttons["FEMALE"]->deactivate();
			}
			else if (it.first == "FEMALE")
			{
				it.second->activate();
				this->buttons["MALE"]->deactivate();
			}
			else if (it.first == "WARRIOR" || it.first == "MAGICIAN" || it.first == "HEALER" || it.first == "NINJA" || it.first == "RANGER")
			{
				it.second->activate();
				if (this->currentClassButton && this->currentClassButton != it.second)
				{
					this->currentClassButton->deactivate();
				}
				this->currentClassButton = it.second;
				if (this->buttons["MALE"]->getActivated())
				{
					this->currentSpriteAnimation->playAnimation(1, 0.001, it.first + "_LEFT_MALE");
					this->currentSpriteAnimation->playAnimation(1, 0.001, it.first + "_DOWN_MALE");
				}
				else if (this->buttons["FEMALE"]->getActivated())
				{
					this->currentSpriteAnimation->playAnimation(1, 0.001, it.first + "_LEFT_FEMALE");
					this->currentSpriteAnimation->playAnimation(1, 0.001, it.first + "_DOWN_FEMALE");
				}
			}
			else if (it.first == "GO")
			{
				this->states->push(new GameState(this->window, this->keys, this->states));
			}
		}
	}
}

void MenuState::render(sf::RenderTarget* target)
{
	if (!target)
		target = this->window;

	target->draw(this->background);
	target->draw(this->title);
	renderButtons(target);
	
	if (this->menuSprite)
	{
		target->draw(*this->menuSprite);
	}
}

void MenuState::renderButtons(sf::RenderTarget * target)
{
	for (auto &it : this->buttons)
	{
		it.second->render(target);
	}
}

void MenuState::initFonts()
{
	if (!this->font.loadFromFile("../External/Fonts/harryp__.ttf"))
	{
		throw("Error in 'MenuState' : Could not load font");
	}
}
/* Initializes @member[buttons] with the parameters in the files "@member[configFile]"
   Format :
		*** First line for title ***
		Name x y w h "Text"- r1 g1 b1 r2 b2 g2 r3 g3 b3 rText gText bText textSize 
		* x y w h in percentage of the window size;
*/
void MenuState::initButtons()
{
	float x_window = this->window->getSize().x, y_window = this->window->getSize().y;

	std::ifstream config_file(this->configFile);
		if (config_file.is_open())
	{
		int i = 0;
		/* Action of the button */
		std::string action = "";
		/* Line in the file */
		std::string line = "";
		/* Coordinates and size of the button */
		float x = 0.0, y = 0.0, w = 0.0, h = 0.0;
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
		while(i < this->numberOfButtons)
		{
			/* Get action */
			std::getline(config_file, action, ' ');

			/* Get coordinates*/
			std::getline(config_file, line, ' ');
			x = static_cast<float>(std::atof(line.c_str())*x_window);

			std::getline(config_file, line, ' ');
			y = static_cast<float>(std::atof(line.c_str())*y_window);

			/* Get size */
			std::getline(config_file, line, ' ');
			w = static_cast<float>(std::atof(line.c_str())*x_window);

			std::getline(config_file, line, ' ');
			h = static_cast<float>(std::atof(line.c_str())*y_window);
			
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
			textSize = (static_cast<float>(std::atof(line.c_str())*x_window));

			/* Create the button */
			this->buttons[action] = new Button(x, y, w, h, text, &this->font, idle_color, hover_color, active_color, text_color, textSize);
			i++;
		}
		config_file.close();
	}
}
/* Initializes @member[title] with the FIRST line in the files ""@member[configFile]"
   Format :
		number_of_buttons x y "Title"- r g b textSize/ <-- end the line with '/'
		*** Other lines ***
		* x y in percentage of the window size
*/
void MenuState::initTitle()
{
	float x_window = this->window->getSize().x, y_window = this->window->getSize().y;

	std::ifstream config_file(this->configFile);

	if (config_file.is_open())
	{
		float x, y;
		float text_size;
		std::string title, line = "";
		sf::Color text_color;

		std::getline(config_file, line, ' ');
		this->numberOfButtons = std::atoi(line.c_str());

		std::getline(config_file, line, ' ');
		x = static_cast<float>(std::atof(line.c_str())*x_window);

		std::getline(config_file, line, ' ');
		y = static_cast<float>(std::atof(line.c_str())*y_window);

		std::getline(config_file, title, '-');

		std::getline(config_file, line, ' ');
		text_color.r = std::atoi(line.c_str());

		std::getline(config_file, line, ' ');
		text_color.g = std::atoi(line.c_str());

		std::getline(config_file, line, ' ');
		text_color.b = std::atoi(line.c_str());

		std::getline(config_file, line, ' ');
		text_size = std::atof(line.c_str())*x_window;

		this->title.setFont(this->font);
		this->title.setFillColor(text_color);
		this->title.setCharacterSize(text_size);
		this->title.setString(title);
		this->title.setPosition(sf::Vector2f(x, y));
		
		config_file.close();
	}
}

void MenuState::initSprites()
{
	std::ifstream config_file("../External/Config/sprites_menu_character.cfg");

	if (config_file.is_open())
	{
		this->menuSprite = new sf::Sprite();

		menuSprite->setPosition(sf::Vector2f(150, 250));
		
		this->currentSpriteAnimation = new AnimationComponent(menuSprite);
		std::string key, path;
		int number_of_textures, width, height;
		float animation_timer;

		while (config_file >> key >> path >> number_of_textures >> width >> height >> animation_timer)
		{
			// Loads appropriate texture
			sf::Texture *texture_sheet = new sf::Texture;
			texture_sheet->loadFromFile(path);
			// Add it to the animation component
			this->currentSpriteAnimation->addAnimation(key, texture_sheet, number_of_textures, width, height, animation_timer);
		}
		config_file.close();
	}

}
