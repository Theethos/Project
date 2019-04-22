#include "Precompiled_Header.h"
#include "../Include/Macros.h"
#include "../Include/MenuState.h"

// Constructor
MenuState::MenuState(sf::RenderWindow *window, std::stack<State*>* states, WhichState state, std::string configFile, Menu menuType) :
State(window, states, state),
menuType(menuType),
numberOfButtons(0),
configFile(configFile), 
activatedButton(nullptr),
joystickMovedX(false),
joystickMovedY(false)
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

	InitFonts();
	InitTitle();
	InitButtons();

	if (this->menuType == Menu::PAUSE_MENU)
	{
		this->background.setSize(sf::Vector2f(this->window->getSize().x / 2, this->window->getSize().y));
		this->background.setPosition(this->window->getSize().x / 4, 0);
		this->background.setFillColor(sf::Color::Transparent);
	}
	else
	{
		this->background.setSize(sf::Vector2f(this->window->getSize()));
		this->background.setFillColor(sf::Color(0, 128, 255));
	}

	if (this->menuType == Menu::CHARACTER_MENU)
	{
		InitSprites();
		InitAnimations();
		// Initialize the sprites background
		sf::Color bgColor = sf::Color::Black;
		bgColor.a = 128;
		this->spritesBackground.setFillColor(bgColor);
		this->spritesBackground.setPosition(sf::Vector2f(
			this->buttons["MALE"]->getPosition().x,
			this->buttons["WARRIOR"]->getPosition().y - 5 * this->spriteScale));
		this->spritesBackground.setSize(sf::Vector2f(
			this->buttons["FEMALE"]->getPosition().x + this->buttons["FEMALE"]->getSize().x - this->buttons["MALE"]->getPosition().x,
			this->buttons["RANGER"]->getPosition().y + this->buttons["RANGER"]->getSize().y - this->buttons["WARRIOR"]->getPosition().y + 15 * this->spriteScale));
	}
	this->selectedButton = std::make_pair(-1, -1);
}
// Destructor
MenuState::~MenuState()
{
	for (auto &it : this->buttons)
	{
		delete it.second;
	}
	for (auto &it : this->sprites)
	{
		delete it.second;
	}
	for (auto &it : this->spritesAnimation)
	{
		delete it.second;
	}

}

// Functions
void MenuState::HandleKeyboardInput(int input, const float &dt)
{
	// Common parts
	if (input == sf::Keyboard::Key(this->actions["VALIDATE"]))
	{
		if (this->selectedButton.first >= 0 && this->selectedButton.second >= 0 && this->buttons.count(this->buttonsText[this->selectedButton.first][this->selectedButton.second]))
			this->buttons[this->buttonsText[this->selectedButton.first][this->selectedButton.second]]->setPressed(true);
	}
	if (input == sf::Keyboard::Key(this->actions["DOWN"]))
	{
		if (this->selectedButton.second < 0)
		{
			this->selectedButton.second = 0;
			if (this->selectedButton.first < 0)
			{
				this->selectedButton.first = 0;
			}
		}
		else
		{
			this->buttons[this->buttonsText[this->selectedButton.first][this->selectedButton.second]]->setHovered(false);
			this->buttons[this->buttonsText[this->selectedButton.first][this->selectedButton.second]]->setSelected(false);
			if (this->selectedButton.second < this->buttonsText[this->selectedButton.first].size() - 1)
			{
				++this->selectedButton.second;
			}
			else
			{
				this->selectedButton.second = 0;
			}
		}
		this->buttons[this->buttonsText[this->selectedButton.first][this->selectedButton.second]]->setHovered(true);
		this->buttons[this->buttonsText[this->selectedButton.first][this->selectedButton.second]]->setSelected(true);
	}
	else if (input == sf::Keyboard::Key(this->actions["UP"]))
	{
		if (this->selectedButton.first < 0)
		{
			this->selectedButton.first = this->buttonsText.size() - 1;
			if (this->selectedButton.second < 0)
			{
				this->selectedButton.second = this->buttonsText[this->selectedButton.first].size() - 1;
			}
		}
		else
		{
			this->buttons[this->buttonsText[this->selectedButton.first][this->selectedButton.second]]->setHovered(false);
			this->buttons[this->buttonsText[this->selectedButton.first][this->selectedButton.second]]->setSelected(false);
			if (this->selectedButton.second != 0)
			{
				--this->selectedButton.second;
			}
			else
			{
				this->selectedButton.second = this->buttonsText[this->selectedButton.first].size() - 1;
			}
		}
		this->buttons[this->buttonsText[this->selectedButton.first][this->selectedButton.second]]->setHovered(true);
		this->buttons[this->buttonsText[this->selectedButton.first][this->selectedButton.second]]->setSelected(true);
	}
	else if  (input == sf::Keyboard::Key(this->actions["RIGHT"]))
	{
		if (this->selectedButton.first < 0)
		{
			this->selectedButton.first = this->buttonsText.size() - 1;
			if (this->selectedButton.second < 0)
			{
				this->selectedButton.second = this->buttonsText[this->selectedButton.first].size() - 1;
			}
		}
		else
		{
			this->buttons[this->buttonsText[this->selectedButton.first][this->selectedButton.second]]->setHovered(false);
			this->buttons[this->buttonsText[this->selectedButton.first][this->selectedButton.second]]->setSelected(false);
			float index = this->selectedButton.second / (this->buttonsText[this->selectedButton.first].size() - 1);
			if (this->selectedButton.first != this->buttonsText.size() - 1)
			{
				++this->selectedButton.first;
			}
			else
			{
				this->selectedButton.first = 0;
			}
			this->selectedButton.second = std::round((this->buttonsText[selectedButton.first].size() - 1)* index);
			if (this->selectedButton.second > this->buttonsText[selectedButton.first].size() - 1)
			{
				this->selectedButton.second = this->buttonsText[selectedButton.first].size() - 1;
			}
		}
		this->buttons[this->buttonsText[this->selectedButton.first][this->selectedButton.second]]->setHovered(true);
		this->buttons[this->buttonsText[this->selectedButton.first][this->selectedButton.second]]->setSelected(true);
	}
	else if  (input == sf::Keyboard::Key(this->actions["LEFT"]))
	{
		if (this->selectedButton.first < 0)
		{
			this->selectedButton.first = this->buttonsText.size() - 1;
			if (this->selectedButton.second < 0)
			{
				this->selectedButton.second = this->buttonsText[this->selectedButton.first].size() - 1;
			}
		}
		else
		{
			this->buttons[this->buttonsText[this->selectedButton.first][this->selectedButton.second]]->setHovered(false);
			this->buttons[this->buttonsText[this->selectedButton.first][this->selectedButton.second]]->setSelected(false);
			float index = this->selectedButton.second / (this->buttonsText[this->selectedButton.first].size() - 1);
			if (this->selectedButton.first != 0)
			{
				--this->selectedButton.first;
			}
			else
			{
				this->selectedButton.first = 0;
			}
			this->selectedButton.second = std::round((this->buttonsText[selectedButton.first].size() - 1)* index);
			if (this->selectedButton.second > this->buttonsText[selectedButton.first].size() - 1)
			{
				this->selectedButton.second = this->buttonsText[selectedButton.first].size() - 1;
			}
		}
		this->buttons[this->buttonsText[this->selectedButton.first][this->selectedButton.second]]->setHovered(true);
		this->buttons[this->buttonsText[this->selectedButton.first][this->selectedButton.second]]->setSelected(true);
	}


	// Specific parts
	switch (this->menuType)
	{
	case Menu::MAIN_MENU:
		break;
	case Menu::PAUSE_MENU:
		if  (input == sf::Keyboard::Key(this->actions["RESUME"]))
			this->quit = true;
		break;
	case Menu::CHARACTER_MENU:
		if  (input == sf::Keyboard::Key(this->actions["QUIT"]))
			this->quit = true;
		break;
	default:
		break;
	}
}

void MenuState::HandleControllerInput(int input, const float &dt)
{
	sf::Vector2f controller_position(sf::Joystick::getAxisPosition(0, sf::Joystick::Axis::X), sf::Joystick::getAxisPosition(0, sf::Joystick::Axis::Y));
	
	// Common parts
	if (input == this->actions["VALIDATE"])
	{
		if (this->selectedButton.first >= 0 && this->selectedButton.second >= 0 && this->buttons.count(this->buttonsText[this->selectedButton.first][this->selectedButton.second]))
			this->buttons[this->buttonsText[this->selectedButton.first][this->selectedButton.second]]->setPressed(true);
	}
	if (controller_position.y > 80 && !this->joystickMovedY)
	{
		this->joystickMovedY = true;
		if (this->selectedButton.second < 0)
		{
			this->selectedButton.second = 0;
			if (this->selectedButton.first < 0)
			{
				this->selectedButton.first = 0;
			}
		}
		else
		{
			this->buttons[this->buttonsText[this->selectedButton.first][this->selectedButton.second]]->setHovered(false);
			this->buttons[this->buttonsText[this->selectedButton.first][this->selectedButton.second]]->setSelected(false);
			if (this->selectedButton.second < this->buttonsText[this->selectedButton.first].size() - 1)
			{
				++this->selectedButton.second;
			}
			else
			{
				this->selectedButton.second = 0;
			}
		}
		this->buttons[this->buttonsText[this->selectedButton.first][this->selectedButton.second]]->setHovered(true);
		this->buttons[this->buttonsText[this->selectedButton.first][this->selectedButton.second]]->setSelected(true);
	}
	else if (controller_position.y < -80 && !this->joystickMovedY)
	{
		this->joystickMovedY = true;
		if (this->selectedButton.first < 0)
		{
			this->selectedButton.first = this->buttonsText.size() - 1;
			if (this->selectedButton.second < 0)
			{
				this->selectedButton.second = this->buttonsText[this->selectedButton.first].size() - 1;
			}
		}
		else
		{
			this->buttons[this->buttonsText[this->selectedButton.first][this->selectedButton.second]]->setHovered(false);
			this->buttons[this->buttonsText[this->selectedButton.first][this->selectedButton.second]]->setSelected(false);
			if (this->selectedButton.second != 0)
			{
				--this->selectedButton.second;
			}
			else
			{
				this->selectedButton.second = this->buttonsText[this->selectedButton.first].size() - 1;
			}
		}
		this->buttons[this->buttonsText[this->selectedButton.first][this->selectedButton.second]]->setHovered(true);
		this->buttons[this->buttonsText[this->selectedButton.first][this->selectedButton.second]]->setSelected(true);
	}
	else if (controller_position.x > 80 && !this->joystickMovedX)
	{
		this->joystickMovedX = true;
		if (this->selectedButton.first < 0)
		{
			this->selectedButton.first = this->buttonsText.size() - 1;
			if (this->selectedButton.second < 0)
			{
				this->selectedButton.second = this->buttonsText[this->selectedButton.first].size() - 1;
			}
		}
		else
		{
			this->buttons[this->buttonsText[this->selectedButton.first][this->selectedButton.second]]->setHovered(false);
			this->buttons[this->buttonsText[this->selectedButton.first][this->selectedButton.second]]->setSelected(false);
			float index = this->selectedButton.second / (this->buttonsText[this->selectedButton.first].size() - 1);
			if (this->selectedButton.first != this->buttonsText.size() - 1)
			{
				++this->selectedButton.first;
			}
			else
			{
				this->selectedButton.first = 0;
			}
			this->selectedButton.second = std::round((this->buttonsText[selectedButton.first].size() - 1)* index);
			if (this->selectedButton.second > this->buttonsText[selectedButton.first].size() - 1)
			{
				this->selectedButton.second = this->buttonsText[selectedButton.first].size() - 1;
			}
		}
		this->buttons[this->buttonsText[this->selectedButton.first][this->selectedButton.second]]->setHovered(true);
		this->buttons[this->buttonsText[this->selectedButton.first][this->selectedButton.second]]->setSelected(true);
	}
	else if (controller_position.x < -80 && !this->joystickMovedX)
	{
		this->joystickMovedX = true;
		if (this->selectedButton.first < 0)
		{
			this->selectedButton.first = this->buttonsText.size() - 1;
			if (this->selectedButton.second < 0)
			{
				this->selectedButton.second = this->buttonsText[this->selectedButton.first].size() - 1;
			}
		}
		else
		{
			this->buttons[this->buttonsText[this->selectedButton.first][this->selectedButton.second]]->setHovered(false);
			this->buttons[this->buttonsText[this->selectedButton.first][this->selectedButton.second]]->setSelected(false);
			float index = this->selectedButton.second / (this->buttonsText[this->selectedButton.first].size() - 1);
			if (this->selectedButton.first != 0)
			{
				--this->selectedButton.first;
			}
			else
			{
				this->selectedButton.first = 0;
			}
			this->selectedButton.second = std::round((this->buttonsText[selectedButton.first].size() - 1) * index);
			if (this->selectedButton.second > this->buttonsText[selectedButton.first].size() - 1)
			{
				this->selectedButton.second = this->buttonsText[selectedButton.first].size() - 1;
			}
		}
		this->buttons[this->buttonsText[this->selectedButton.first][this->selectedButton.second]]->setHovered(true);
		this->buttons[this->buttonsText[this->selectedButton.first][this->selectedButton.second]]->setSelected(true);
	}

	// Specific parts
	switch (this->menuType)
	{
	case Menu::MAIN_MENU:
		break;
	case Menu::PAUSE_MENU:
		if (input == this->actions["RESUME"])
			this->quit = true;
		break;
	case Menu::CHARACTER_MENU:
		if (input == this->actions["QUIT"])
			this->quit = true;
		break;
	default:
		break;
	}
}

void MenuState::Update(const float& dt)
{
	UpdateMousePositions();
	
	UpdateButtons();

	UpdateCursor();

	sf::Vector2f controller_position(sf::Joystick::getAxisPosition(0, sf::Joystick::Axis::X), sf::Joystick::getAxisPosition(0, sf::Joystick::Axis::Y));

	if (controller_position.y > -20 && controller_position.y < 20)
		this->joystickMovedY = false;
	if (controller_position.x > -20 && controller_position.x < 20)
		this->joystickMovedX = false;
}

void MenuState::UpdateButtons()
{
	for (auto &it : this->buttons)
	{
		it.second->Update(this->mousePosView);
		if (it.second->getPressed())
		{
			// Main Menu
			if (it.first == "NEW_GAME")
			{
				if (it.second->getSelected())
				{
					it.second->setSelected(false);
					this->selectedButton = std::make_pair(-1, -1);
				}
				it.second->setPressed(false);
				this->states->push(new MenuState(this->window, this->states, WhichState::MENU_STATE, "../External/Config/Buttons/Choose_character_menu.cfg", Menu::CHARACTER_MENU));
			}
			else if (it.first == "QUIT")
			{
				this->window->close();
			}
			// Pause Menu
			else if (it.first == "RESUME")
			{
				this->quit = true;
			}
			else if (it.first == "MAIN_MENU")
			{
				if (this->menuType == Menu::CHARACTER_MENU)
				{
					this->quit = true;
				}
				else
				{
					this->states->push(new MenuState(this->window, this->states, WhichState::MENU_STATE, "../External/Config/Buttons/Main_menu.cfg", Menu::MAIN_MENU));
				}
			}
			else if (it.first == "SETTINGS")
			{
			}
			// Choose Character Menu
			else if (it.first == "MALE")
			{
				it.second->Activate();
				this->buttons["FEMALE"]->Deactivate();
				this->buttons["PSEUDO"]->Deactivate();
				it.second->setPressed(false);
			}
			else if (it.first == "FEMALE")
			{
				it.second->Activate();
				this->buttons["MALE"]->Deactivate();
				this->buttons["PSEUDO"]->Deactivate();
				it.second->setPressed(false);
			}
			else if (it.first == "WARRIOR" || it.first == "MAGICIAN" || it.first == "HEALER" || it.first == "NINJA" || it.first == "RANGER")
			{
				it.second->Activate();
				this->activatedClass = it.first;
				if (this->activatedButton && this->activatedButton != it.second)
				{
					this->activatedButton->Deactivate();
				}
				this->activatedButton = it.second;
				this->buttons["PSEUDO"]->Deactivate();
				it.second->setPressed(false);
			}
			else if (it.first == "GO")
			{
				// Passing the right sprite's animations
				std::string path_to_sprite;
				if (this->buttons["MALE"]->getActivated())
				{
					path_to_sprite = "../External/Config/Character_Class/" + this->activatedClass + "_MALE.cfg";
				}
				else if (this->buttons["FEMALE"]->getActivated())
				{
					path_to_sprite = "../External/Config/Character_Class/"+ this->activatedClass + "_FEMALE.cfg";
				}

				// Reset the button
				it.second->setPressed(false);

				// Checking if the player chose a pseudo
				ButtonText* button = static_cast<ButtonText*>(this->buttons["PSEUDO"]);
				if (button->getTextEntered() == "")
				{
					button->Blink();
				}
				else
				{
					this->states->push(new GameState(this->window, this->states, WhichState::GAME_STATE, path_to_sprite, this->spriteScale, button->getTextEntered(), &this->font["ALL"]));
				}

				this->buttons["PSEUDO"]->Deactivate();
			}
			else if (it.first == "PSEUDO")
			{
				it.second->Activate();
				it.second->setPressed(false);
			}
		}
	}
}

void MenuState::UpdateCursor()
{
	if (this->buttons.count("PSEUDO"))
	{
		if (this->buttons["PSEUDO"]->getHovered())
		{
			if (this->buttons["PSEUDO"]->getActivated())
			{
				this->window->setMouseCursorVisible(false);
			}
			else
			{
				this->cursor.loadFromSystem(sf::Cursor::Text);
				this->window->setMouseCursor(cursor);
			}
		}
		else
		{
			this->cursor.loadFromSystem(sf::Cursor::Arrow);
			this->window->setMouseCursor(cursor);
			this->window->setMouseCursorVisible(true);
			if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
			{
				this->buttons["PSEUDO"]->Deactivate();
			}
		}
	}
}

void MenuState::Render(sf::RenderTarget* target)
{
	if (!target)
		target = this->window;

	target->draw(this->background);
	target->draw(this->title);
	this->RenderButtons(target);
	
	if (this->menuType == Menu::CHARACTER_MENU)
	{
		target->draw(this->spritesBackground);
		this->RenderSprites(target);
	}
}

void MenuState::RenderButtons(sf::RenderTarget * target)
{
	for (auto &it : this->buttons)
	{
		it.second->Render(target);
	}
}

void MenuState::RenderSprites(sf::RenderTarget * target)
{
	sf::Vector2f sprite_position;
	// If user selected "male"
	if (this->buttons["MALE"]->getActivated())
	{
		// Set the position of the sprite on the left (the first one)
		sprite_position = sf::Vector2f(this->buttons["MALE"]->getPosition().x + this->sprites["LEFT"]->getGlobalBounds().width , this->buttons[activatedClass]->getPosition().y);
		// For each sprite
		for (auto &it : sprites)
		{
			// Update its position
			it.second->setPosition(sprite_position);
			// Play the right animation
			this->spritesAnimation[it.first]->PlayAnimation(1, 0.005, activatedClass + "_" + it.first + "_MALE");
			// Update the position of the next sprite
			sprite_position.x += 20 * this->spriteScale;
		}
	}
	// Same if user selects "female"
	else if (this->buttons["FEMALE"]->getActivated())
	{
		sprite_position = sf::Vector2f(this->buttons["FEMALE"]->getPosition().x + 1.5 * this->sprites["LEFT"]->getGlobalBounds().width, this->buttons[activatedClass]->getPosition().y);
		for (auto &it : sprites)
		{
			it.second->setPosition(sprite_position);
			this->spritesAnimation[it.first]->PlayAnimation(1, 0.005, activatedClass + "_" + it.first + "_FEMALE");
			sprite_position.x += 20 * this->spriteScale;
		}
	}
	// Draw all the sprites
	for (auto &it : sprites)
	{
		target->draw(*it.second);
	}
}

void MenuState::InitFonts()
{
	if (!this->font["TITLE"].loadFromFile("../External/Fonts/harryp__.ttf"))
	{
		std::cerr << "Error in 'MenuState' : Could not load \"harryp__.ttf\" font\n";
	}
	if (!this->font["ALL"].loadFromFile("../External/Fonts/GOTHICB.TTF"))
	{
		std::cerr << "Error in 'MenuState' : Could not load \"GOTHICB.TTF\" font\n";
	}
}
/////////////////////////////////////////////////////////////////////
/// Initializes the map of buttons with the parameters in the file this->configFile
/// Format :
///	--- First line for title ---
///	Name >> x >> y >> w >> h >> "Text"- >> r1 >> g1 >> b1 >> r2 >> b2 >> g2 >> r3 >> g3 >> b3 >> rText >> gText >> bText >> textSize >> navigation_row
///	--> x, y, w, and h in percentage of the window size
/////////////////////////////////////////////////////////////////////
void MenuState::InitButtons()
{
	float x_window = this->window->getSize().x, y_window = this->window->getSize().y;

	std::ifstream config_file(this->configFile);
	if (config_file.is_open())
	{
		int i = 0;
		int button_type = 0;
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
		sf::Color idle_color = sf::Color::White, hover_color = sf::Color::White, active_color = sf::Color::White;
		/* Size of the text on the button */
		float textSize = 12.0;
		int navigation_row = 0;

		/* Skip the first line */
		std::getline(config_file, line, '\n');

		/* For each buttons of this state */
		while(i < this->numberOfButtons)
		{
			/* get button_type */
			std::getline(config_file, line, ' ');
			button_type = static_cast<int>(std::atoi(line.c_str()));

			/* get action */
			std::getline(config_file, action, ' ');

			/* get coordinates*/
			std::getline(config_file, line, ' ');
			x = static_cast<float>(std::atof(line.c_str())*x_window);

			std::getline(config_file, line, ' ');
			y = static_cast<float>(std::atof(line.c_str())*y_window);

			/* get size */
			std::getline(config_file, line, ' ');
			w = static_cast<float>(std::atof(line.c_str())*x_window);

			std::getline(config_file, line, ' ');
			h = static_cast<float>(std::atof(line.c_str())*y_window);
			
			/* get text */
			std::getline(config_file, text, '-');

			/* get Idle_Color */
			std::getline(config_file, line, ' ');
			idle_color.r = std::atoi(line.c_str());

			std::getline(config_file, line, ' ');
			idle_color.g = std::atoi(line.c_str());

			std::getline(config_file, line, ' ');
			idle_color.b = std::atoi(line.c_str());

			/* get Hover_Color */
			std::getline(config_file, line, ' ');
			hover_color.r = std::atoi(line.c_str());

			std::getline(config_file, line, ' ');
			hover_color.g = std::atoi(line.c_str());

			std::getline(config_file, line, ' ');
			hover_color.b = std::atoi(line.c_str());

			/* get Active_Color */
			std::getline(config_file, line, ' ');
			active_color.r = std::atoi(line.c_str());

			std::getline(config_file, line, ' ');
			active_color.g = std::atoi(line.c_str());

			std::getline(config_file, line, ' ');
			active_color.b = std::atoi(line.c_str());

			/* get Text_size */
			std::getline(config_file, line, ' ');
			textSize = (static_cast<float>(std::atof(line.c_str())*x_window));

			/* get navigation_row */
			std::getline(config_file, line, '\n');
			navigation_row = static_cast<int>(std::atoi(line.c_str()));

			/* Create the button */
			switch (button_type)
			{
			case 0:
				this->buttons[action] = new Button(x, y, w, h, text, &this->font["ALL"], idle_color, hover_color, active_color, textSize);
				break;
			case 1:
				this->buttons[action] = new ButtonText(x, y, w, h, text, &this->font["ALL"], idle_color, hover_color, active_color, textSize, this->window);
				break;
			default:
				break;
			}
			if (navigation_row == this->buttonsText.size())
			{
				std::vector<std::string> new_row;
				this->buttonsText.push_back(new_row);
			}
			this->buttonsText[navigation_row].push_back(action);
			i++;
		}
		config_file.close();
	}
}
/////////////////////////////////////////////////////////////////////
/// Initializes @member[title] with the FIRST line in the file this->configFile
/// Format :
///	number_of_buttons >> x >> y >> "Title"- >> rText >> gText >> bText >> textSize/ <-- end the line with '/'
///	*** Other lines ***
///	--> x and y in percentage of the window size
/////////////////////////////////////////////////////////////////////
void MenuState::InitTitle()
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

		this->title.setFont(this->font["TITLE"]);
		this->title.setFillColor(text_color);
		this->title.setCharacterSize(text_size);
		this->title.setString(title);
		this->title.setPosition(sf::Vector2f(x, y));
		
		config_file.close();
	}
}
/////////////////////////////////////////////////////////////////////
/// Initializes the map of sprites and the sprite_scale depending on the screen size
/////////////////////////////////////////////////////////////////////
void MenuState::InitSprites()
{
	this->sprites["LEFT"] = new sf::Sprite();
	this->sprites["DOWN"] = new sf::Sprite();
	this->sprites["UP"] = new sf::Sprite();
	this->sprites["RIGHT"] = new sf::Sprite();

	this->spriteScale = this->window->getSize().y / 270; // Equals to 4 in 1920 x 1080
	for (auto &it : this->sprites)
	{
		it.second->setScale(this->spriteScale, this->spriteScale);
	}
}
/////////////////////////////////////////////////////////////////////
/// Initializes the map of Animatins with the parameters in the file "Sprites/Sprites.cfg"
/// Format :
///	animation_component >> animation_key >> texture_sheet_path >> number_of_textures >> width >> height >> animation_timer 
/////////////////////////////////////////////////////////////////////
void MenuState::InitAnimations()
{
	std::ifstream config_file("../External/Config/Sprites/Sprites.cfg");

	if (config_file.is_open())
	{
		// Creating Animation for each sprite
		for (auto &it : sprites)
		{
			this->spritesAnimation[it.first] = new AnimationComponent(it.second);
		}

		std::string animation_component, animation_key, texture_sheet_path;
		int number_of_textures, width, height;
		float animation_timer;

		while (config_file >> animation_component >> animation_key >> texture_sheet_path >> number_of_textures >> width >> height >> animation_timer)
		{
			// Loads appropriate texture
			sf::Texture *texture_sheet = new sf::Texture;
			texture_sheet->loadFromFile(texture_sheet_path);
			// Add it to the animation component
			this->spritesAnimation[animation_component]->AddAnimation(animation_key, texture_sheet, number_of_textures, width, height, animation_timer);
		}

		config_file.close();

		// Display the warrior male by default
		this->buttons["WARRIOR"]->Activate();
		this->buttons["MALE"]->Activate();
		this->activatedButton = this->buttons["WARRIOR"];
		this->activatedClass = "WARRIOR";
	}
}

// Getter
const Menu & MenuState::getMenuType() const
{
	return this->menuType;
}
