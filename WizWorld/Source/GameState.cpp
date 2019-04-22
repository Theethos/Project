#include "Precompiled_Header.h"
#include "../Include/Macros.h"
#include "../Include/GameState.h"
#include "../Include/MenuState.h"

// Function to tranform std::string in AnimationSide::side \see CheckSpriteCollision()
AnimationSide StringToSide(std::string side)
{
	if (side == "LEFT")
	{
		return AnimationSide::LEFT;
	}
	else if (side == "RIGHT")
	{
		return AnimationSide::RIGHT;
	}
	else if (side == "DOWN")
	{
		return AnimationSide::DOWN;
	}
	else if (side == "UP")
	{
		return AnimationSide::UP;
	}
}

// Construtor
GameState::GameState(sf::RenderWindow *window, std::stack<State*>* states, WhichState state, std::string config_file, int sprite_scale, std::string player_name, sf::Font* player_name_font) :
State(window, states, state), 
movementLocked(false),
transition(window->getSize())
{
	InitMaps(sprite_scale);
	this->player = new Player(2.f, 0.0, 0.0, config_file, player_name, player_name_font, sprite_scale);

	this->playerView.setSize(this->window->getSize().x, this->window->getSize().y);
	this->player->getSprite()->setPosition(this->maps[currentMap]->getSize().x * sprite_scale / 2, this->maps[currentMap]->getSize().y * sprite_scale / 2);

	InitView();

	// Display the area where the camera can move (Render it to see)
	this->viewMovementArea.setFillColor(sf::Color::Transparent);
	this->viewMovementArea.setOutlineColor(sf::Color::Red);
	this->viewMovementArea.setOutlineThickness(1);
	this->viewMovementArea.setPosition(this->viewLocked["LEFT"], this->viewLocked["UP"]);
	this->viewMovementArea.setSize(sf::Vector2f(this->viewLocked["RIGHT"] - (this->window->getSize().y / 2), this->viewLocked["DOWN"] - (this->window->getSize().y / 2)));
}
// Destructor
GameState::~GameState()
{
	delete this->player;
	for (auto &it : this->maps)
	{
		delete it.second;
	}
	for (auto &it : this->collisionMaps)
	{
		delete it.second;
	}
}

// Functions
void GameState::HandleInput(int input, const float & dt)
{
	// Open pause menu when "Options" or "Escape" is pressed
	if (input == (sf::Joystick::isConnected(0) ? this->actions["PAUSE"] : sf::Keyboard::Key(this->actions["PAUSE"])))
	{
		this->states->push(new MenuState(this->window, this->states, WhichState::MENU_STATE, "../External/Config/Buttons/Pause_menu.cfg", Menu::PAUSE_MENU));
	}
	// Makes the player run
	bool running = false;
	if (sf::Joystick::isButtonPressed(0, this->actions["RUN"]) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->actions["RUN"])))
	{
		this->player->getMovement()->setMaxVelocity(3.f);
		running = true;
	}
	else
	{
		this->player->getMovement()->setMaxVelocity(2.f);
	}

	sf::Vector2f controller_position(sf::Joystick::getAxisPosition(0, sf::Joystick::Axis::X), sf::Joystick::getAxisPosition(0, sf::Joystick::Axis::Y));

	if (!this->movementLocked)
	{
		if (controller_position.y < -80 || sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->actions["UP"])))
		{
			if (!this->CheckSpriteCollision(dt, "UP"))
			{
				this->player->getMovement()->setVelocityX(0);
				this->player->Move(dt, 0.f, (running ? -2.f : -1.f));
				this->previousMove = "UP";
				ResetView();
			}
		}
		else if (controller_position.y > 80 || sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->actions["DOWN"])))
		{
			if (!this->CheckSpriteCollision(dt, "DOWN"))
			{
				this->player->getMovement()->setVelocityX(0);
				this->player->Move(dt, 0.f, (running ? 2.f : 1.f));
				this->previousMove = "DOWN";
				ResetView();
			}
		}
		else if (controller_position.x < -80 || sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->actions["LEFT"])))
		{
			if (!this->CheckSpriteCollision(dt, "LEFT"))
			{
				this->player->getMovement()->setVelocityY(0);
				this->player->Move(dt, (running ? -2.f : -1.f), 0.f);
				this->previousMove = "LEFT";
				ResetView();
			}
		}
		else if (controller_position.x > 80 || sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->actions["RIGHT"])))
		{
			if (!this->CheckSpriteCollision(dt, "RIGHT"))
			{
				this->player->getMovement()->setVelocityY(0);
				this->player->Move(dt, (running ? 2.f : 1.f), 0.f);
				this->previousMove = "RIGHT";
				ResetView();
			}
		}
	}
}

void GameState::ChangeMap(sf::Color color)
{
	if (this->currentMap == "Courtyard")
	{
		if (color == sf::Color::Blue)
		{
			this->currentMap = "Hogwarts_Hallways";
			this->player->getSprite()->setPosition(this->maps[currentMap]->getStartingPosition("START"));
			ResetView(true);
		}
		else if (color == sf::Color::Green)
		{
			this->currentMap = "Library";
			this->player->getSprite()->setPosition(this->maps[currentMap]->getStartingPosition("START"));
			ResetView(true);
		}
		else if (color == sf::Color::Yellow)
		{
			this->currentMap = "Potions_Room";
			this->player->getSprite()->setPosition(this->maps[currentMap]->getStartingPosition("START"));
			ResetView(true);
		}
		else if (color == sf::Color::Magenta)
		{
			this->currentMap = "The_Great_Hall";
			this->player->getSprite()->setPosition(this->maps[currentMap]->getStartingPosition("START"));
			ResetView(true);
		}
	}
	else if (this->currentMap == "Hogwarts_Hallways")
	{
		if (color == sf::Color::Red)
		{

		}
		else if (color == sf::Color::Red)
		{

		}
		else if (color == sf::Color::Red)
		{
		}
	}
	else if (this->currentMap == "Library")
	{
		if (color == sf::Color::Red)
		{

		}
		else if (color == sf::Color::Red)
		{

		}
		else if (color == sf::Color::Red)
		{

		}
	}
	else if (this->currentMap == "Potions_Room")
	{
		if (color == sf::Color::Blue)
		{
			this->player->getSprite()->setPosition(this->maps[currentMap]->getStartingPosition("FROM_BLUE"));
			ResetView();
		}
		else if (color == sf::Color::Magenta)
		{
			this->player->getSprite()->setPosition(this->maps[currentMap]->getStartingPosition("FROM_MAGENTA"));
			ResetView();
		}
		else if (color == sf::Color::Green)
		{
			this->currentMap = "Library";
			this->player->getSprite()->setPosition(this->maps[currentMap]->getStartingPosition("START"));
			ResetView(true);
		}
	}
	else if (this->currentMap == "The_Great_Hall")
	{
		if (color == sf::Color::Magenta)
		{
			this->player->getSprite()->setPosition(this->maps[currentMap]->getStartingPosition("FROM_BLUE"));
			ResetView();
		}
		else if (color == sf::Color::Blue)
		{
			this->player->getSprite()->setPosition(this->maps[currentMap]->getStartingPosition("FROM_MAGENTA"));
			ResetView();
		}
		else if (color == sf::Color::Red)
		{

		}
	}
}

void GameState::Update(const float& dt)
{
	UpdateMousePositions();

	HandleInput(-1, dt);

	this->player->Update(dt);

	if (this->movementLocked)
	{
		this->transition.Update();
		if (this->transition.getStatus() == TransitionStatus::HALF)
		{
			ChangeMap(this->transitionColor);
		}
		else if (this->transition.getStatus() == TransitionStatus::COMPLETE)
		{
			this->movementLocked = false;
		}
	}
}

void GameState::Render(sf::RenderTarget* target)
{
	if (!target)
		target = this->window;

	// Change the view
	target->setView(this->playerView);
	this->maps[currentMap]->Render(target);
	this->player->Render(target);
	//target->draw(this->viewMovementArea); // Render the camera area

	// Reset the view
	target->setView(this->window->getDefaultView());
	if (this->movementLocked)
	{
		this->transition.Render(target);
	}
}

/////////////////////////////////////////////////////////////////////
/// Initializes the map of Maps with the parameters in the files "Maps/Maps.cfg"
/// Format : 
/// Map_name >> map_path >> collision_map_path
/////////////////////////////////////////////////////////////////////
void GameState::InitMaps(int scale)
{
	std::ifstream config_file("../External/Config/Maps/Maps.cfg");
	if (config_file.is_open())
	{
		std::string map_name = "", map_path = "", collision_map_path = "", starting_position = "";
		while (config_file >> map_name >> map_path >> collision_map_path >> starting_position)
		{
			this->maps[map_name] = new Map(map_path, scale);
			this->maps[map_name]->InitPositions(starting_position);
			this->collisionMaps[map_name] = new Map(collision_map_path, scale, true);
		}
		config_file.close();
	}
	this->currentMap = "Courtyard";
}

void GameState::InitView()
{
	int sprite_scale = this->player->getSprite()->getScale().x;
	// These are the limits for the movement of the camera. If the player goes behond, the camera stops moving
	this->viewLocked["LEFT"] = this->maps[currentMap]->getPosition().x + this->window->getSize().x / 2;
	this->viewLocked["RIGHT"] = this->maps[currentMap]->getPosition().x + (this->maps[currentMap]->getSize().x * sprite_scale) - (this->window->getSize().x / 2);
	this->viewLocked["UP"] = this->maps[currentMap]->getPosition().y + this->window->getSize().y / 2;
	this->viewLocked["DOWN"] = this->maps[currentMap]->getPosition().y + (this->maps[currentMap]->getSize().y * sprite_scale) - (this->window->getSize().y / 2);

	sf::Vector2f sprite_size(this->player->getSprite()->getGlobalBounds().width, this->player->getSprite()->getGlobalBounds().height);

	this->playerView.setCenter(this->player->getSprite()->getPosition().x + sprite_size.x / 2, this->player->getSprite()->getPosition().y + sprite_size.y / 2);
}

void GameState::ResetView(bool new_map)
{
	sf::Vector2f sprite_size(this->player->getSprite()->getGlobalBounds().width, this->player->getSprite()->getGlobalBounds().height);

	// If the map changes, we have to modify the previous value of viewLocked
	if (new_map)
		InitView();
	else
		this->playerView.setCenter(this->player->getSprite()->getPosition().x + sprite_size.x / 2, this->player->getSprite()->getPosition().y + sprite_size.y / 2);

	if (this->playerView.getCenter().x < this->viewLocked["LEFT"])
	{
		this->playerView.setCenter(this->viewLocked["LEFT"], this->playerView.getCenter().y);
	}
	else if (this->playerView.getCenter().x >= this->viewLocked["RIGHT"])
	{
		this->playerView.setCenter(this->viewLocked["RIGHT"] - 1, this->playerView.getCenter().y);
	}
	if (this->playerView.getCenter().y < this->viewLocked["UP"])
	{
		this->playerView.setCenter(this->playerView.getCenter().x, this->viewLocked["UP"]);
	}
	else if (this->playerView.getCenter().y >= this->viewLocked["DOWN"])
	{
		this->playerView.setCenter(this->playerView.getCenter().x, this->viewLocked["DOWN"] - 1);
	}
}

bool GameState::CheckSpriteCollision(const float & dt,std::string movement)
{
	// Collision are tested on a copy of the map (collisionMaps). The areas that can't be crossed by the player are in red (255, 0, 0).
	sf::Vector2f sprite_position = sf::Vector2f(this->player->getSprite()->getPosition().x / this->collisionMaps[currentMap]->getScale(), this->player->getSprite()->getPosition().y / this->collisionMaps[currentMap]->getScale());
	sprite_position = sf::Vector2f(std::roundl(sprite_position.x), std::roundl(sprite_position.y));

	sf::Vector2f sprite_size = sf::Vector2f(this->player->getSprite()->getGlobalBounds().width / this->collisionMaps[currentMap]->getScale(), this->player->getSprite()->getGlobalBounds().height / this->collisionMaps[currentMap]->getScale());

	sf::Color pixel_toward_color[3];

	if (movement == "UP")
	{
		pixel_toward_color[0] = this->collisionMaps[currentMap]->getPixelColor(sprite_position.x + 1, sprite_position.y + sprite_size.y - 1);
		pixel_toward_color[1] = this->collisionMaps[currentMap]->getPixelColor(sprite_position.x + sprite_size.x / 2 , sprite_position.y - 1 + sprite_size.y);
		pixel_toward_color[2] = this->collisionMaps[currentMap]->getPixelColor(sprite_position.x - 1 + sprite_size.x, sprite_position.y - 1 + sprite_size.y);
	}
	else if (movement == "DOWN")
	{
		pixel_toward_color[0] = this->collisionMaps[currentMap]->getPixelColor(sprite_position.x + 1, sprite_position.y + sprite_size.y + 1);
		pixel_toward_color[1] = this->collisionMaps[currentMap]->getPixelColor(sprite_position.x + sprite_size.x / 2, sprite_position.y + sprite_size.y + 1);
		pixel_toward_color[2] = this->collisionMaps[currentMap]->getPixelColor(sprite_position.x - 1 + sprite_size.x, sprite_position.y + sprite_size.y + 1);
	}
	else if (movement == "LEFT")
	{
		pixel_toward_color[0] = this->collisionMaps[currentMap]->getPixelColor(sprite_position.x - 1, std::min(sprite_position.y + sprite_size.y, this->maps[currentMap]->getSize().y));
		// Others are not required
		pixel_toward_color[1] = sf::Color::Black;
		pixel_toward_color[2] = sf::Color::Black;
	}
	else if (movement == "RIGHT")
	{
		pixel_toward_color[0] = this->collisionMaps[currentMap]->getPixelColor(sprite_position.x + sprite_size.x + 1, std::min(sprite_position.y + sprite_size.y, this->maps[currentMap]->getSize().y));
		pixel_toward_color[1] = sf::Color::Black;
		pixel_toward_color[2] = sf::Color::Black;
	}
	for (auto &it : pixel_toward_color)
	{
		if (it == sf::Color::Red)
		{
			this->player->getMovement()->setVelocity(0, 0);
			this->player->getAnimation()->PlayAnimation(0, dt, movement);
			std::string side = movement.replace(movement.begin(), movement.begin() + 5, "");
			this->player->getAnimation()->setSide(StringToSide(side));
			return true;
		}
		else if (it == sf::Color::Magenta || it == sf::Color::Blue || it == sf::Color::Green || it == sf::Color::Yellow)
		{
			this->movementLocked = true;
			this->transitionColor = it;
			return true;
		}
	}
	return false;
}