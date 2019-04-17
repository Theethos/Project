#include "Precompiled_Header.h"
#include "../Include/Macros.h"
#include "../Include/MenuState.h"

// Constructor
MenuState::MenuState(sf::RenderWindow *window, std::map < std::string, int> *keys, std::stack<State*>* states, WhichState state, std::string configFile, Menu menuType) :
State(window, keys, states, state), 
numberOfButtons(0),
configFile(configFile), 
selectedButton(nullptr),
menuType(menuType)
{
	InitFonts();
	InitTitle();
	InitButtons();

	this->background.setSize(sf::Vector2f(this->window->getSize()));

	// Loads the background's image depending on the size of the window
	//if (this->backgroundTexture.loadFromFile("../External/Images/Background/"+std::to_string(this->window->getSize().x)+"_"+ std::to_string(this->window->getSize().y)+".png"))
	//	this->background.setTexture(&this->backgroundTexture);
	// if the file does not exist
	//else
	{
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
void MenuState::HandleInput(const float &dt)
{}

void MenuState::Update(const float& dt)
{
	this->UpdateMousePositions();
	
	this->UpdateButtons();

	this->UpdateCursor();
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
				it.second->setPressed(false);
				this->states->push(new MenuState(this->window, this->keys, this->states, WhichState::MENU_STATE, "../External/Config/choose_character_buttons.cfg", Menu::CHARACTER_MENU));
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
					it.second->setPressed(false);
					this->states->push(new MenuState(this->window, this->keys, this->states, WhichState::MENU_STATE, "../External/Config/main_menu_buttons.cfg", Menu::MAIN_MENU));
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
			}
			else if (it.first == "FEMALE")
			{
				it.second->Activate();
				this->buttons["MALE"]->Deactivate();
				this->buttons["PSEUDO"]->Deactivate();
			}
			else if (it.first == "WARRIOR" || it.first == "MAGICIAN" || it.first == "HEALER" || it.first == "NINJA" || it.first == "RANGER")
			{
				it.second->Activate();
				this->selectedClass = it.first;
				if (this->selectedButton && this->selectedButton != it.second)
				{
					this->selectedButton->Deactivate();
				}
				this->selectedButton = it.second;
				this->buttons["PSEUDO"]->Deactivate();
			}
			else if (it.first == "GO")
			{
				// Passing the right sprite's animations
				std::string path_to_sprite;
				if (this->buttons["MALE"]->getActivated())
				{
					path_to_sprite = "../External/Config/Character_Class/" + this->selectedClass + "_MALE.cfg";
				}
				else if (this->buttons["FEMALE"]->getActivated())
				{
					path_to_sprite = "../External/Config/Character_Class/"+ this->selectedClass + "_FEMALE.cfg";
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
					this->states->push(new GameState(this->window, this->keys, this->states, WhichState::GAME_STATE, path_to_sprite, this->spriteScale, button->getTextEntered(), &this->font["ALL"]));
				}

				this->buttons["PSEUDO"]->Deactivate();
			}
			else if (it.first == "PSEUDO")
			{
				it.second->Activate();
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
		sprite_position = sf::Vector2f(this->buttons["MALE"]->getPosition().x + this->sprites["LEFT"]->getGlobalBounds().width , this->buttons[selectedClass]->getPosition().y);
		// For each sprite
		for (auto &it : sprites)
		{
			// Update its position
			it.second->setPosition(sprite_position);
			// Play the right animation
			this->spritesAnimation[it.first]->PlayAnimation(1, 0.005, selectedClass + "_" + it.first + "_MALE");
			// Update the position of the next sprite
			sprite_position.x += 20 * this->spriteScale;
		}
	}
	// Same if user selects "female"
	else if (this->buttons["FEMALE"]->getActivated())
	{
		sprite_position = sf::Vector2f(this->buttons["FEMALE"]->getPosition().x + 1.5 * this->sprites["LEFT"]->getGlobalBounds().width, this->buttons[selectedClass]->getPosition().y);
		for (auto &it : sprites)
		{
			it.second->setPosition(sprite_position);
			this->spritesAnimation[it.first]->PlayAnimation(1, 0.005, selectedClass + "_" + it.first + "_FEMALE");
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
/* Initializes @member[buttons] with the parameters in the file "@member[configFile]"
   Format :
		*** First line for title ***
		Name x y w h "Text"- r1 g1 b1 r2 b2 g2 r3 g3 b3 rText gText bText textSize 
		* x y w h in percentage of the window size;
*/
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
			std::getline(config_file, line, '\n');
			textSize = (static_cast<float>(std::atof(line.c_str())*x_window));

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
			i++;
		}
		config_file.close();
	}
}
/* Initializes @member[title] with the FIRST line in the file ""@member[configFile]"
   Format :
		number_of_buttons x y Title'-' r g b textSize/ <-- end the line with '/'
		*** Other lines ***
		* x y in percentage of the window size
*/
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
/* Initializes @member[Sprites] and the sprite_scale depending on the screen size */
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
/* Initializes @member[title] with the the parameters in the file "@member[configFile]"
   Format :
		animation_component animation_key texture_sheet_path number_of_textures width height animation_timer
*/
void MenuState::InitAnimations()
{
	std::ifstream config_file("../External/Config/sprites_menu_character.cfg");

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
		this->selectedButton = this->buttons["WARRIOR"];
		this->selectedClass = "WARRIOR";
	}
}

// Getter
const Menu & MenuState::getMenuType() const
{
	return this->menuType;
}
