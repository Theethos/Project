#include "Precompiled_Header.h"
#include "../Include/Macros.h"
#include "../Include/GameState.h"
#include "../Include/MenuState.h"

// Function to tranform std::string in AnimationSide::side
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
GameState::GameState(sf::RenderWindow *window, std::map < std::string, int> *keys, std::stack<State*>* states, WhichState state, std::string config_file, int sprite_scale, std::string player_name, sf::Font* player_name_font) : 
State(window, keys, states, state)
{
	InitActions();
	this->player = new Player(1.5f, 0.0, 0.0, config_file, player_name, player_name_font, sprite_scale);
	this->map = new Map("../External/Images/Map/Visible/Courtyard.png", sprite_scale);
	this->collidedMap = new Map("../External/Images/Map/Collision/Courtyard.png", sprite_scale);

	this->playerView.setSize(this->window->getSize().x, this->window->getSize().y);
	this->player->getSprite()->setPosition(this->map->getSize().x * sprite_scale / 2, this->map->getSize().y * sprite_scale / 2);
	this->playerView.setCenter(this->player->getSprite()->getPosition());

	// These are the limits for the movement of the camera. If the player goes behond, the camera stops moving
	this->viewLocked["LEFT"] = this->map->getPosition().x + this->window->getSize().x / 2;
	this->viewLocked["RIGHT"] = this->map->getPosition().x + (this->map->getSize().x * sprite_scale) - (this->window->getSize().x / 2);
	this->viewLocked["UP"] = this->map->getPosition().y + this->window->getSize().y / 2;
	this->viewLocked["DOWN"] = this->map->getPosition().y + (this->map->getSize().y * sprite_scale) - (this->window->getSize().y / 2);

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
	delete this->map;
}

// Functions
void GameState::HandleInput(const float &dt)
{
	sf::Vector2f sprite_current_position = this->player->getSprite()->getPosition();
	// Move the character in the direction given by input
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->actions["MOVE_UP"])))
	{
		// Check that the player doesn't collid anything
		if (!this->CheckSpriteCollision(dt ,"MOVE_UP"))
		{
			this->player->Move(dt, 0.f, -1.f);
			// Check if the camera can move
			if (!this->CheckViewPosition("MOVE_UP"))
				// * 2 * is in hard, don't know why but otherwise the camera is slower than the player
				this->playerView.move(0.f, 1.f * 2 * this->player->getMovement()->getVelocity().y);
		} 
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->actions["MOVE_DOWN"])))
	{
		if (!this->CheckSpriteCollision(dt, "MOVE_DOWN"))
		{
			this->player->Move(dt, 0.f, 1.f);
			if (!this->CheckViewPosition("MOVE_DOWN"))
				this->playerView.move(0.f, 1.f * 2 * this->player->getMovement()->getVelocity().y);
		}
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->actions["MOVE_LEFT"])))
	{
		if (!this->CheckSpriteCollision(dt, "MOVE_LEFT"))
		{
			this->player->Move(dt, -1.f, 0.f);
			if (!this->CheckViewPosition("MOVE_LEFT"))
				this->playerView.move(1.f * 2 * this->player->getMovement()->getVelocity().x, 0.f);
		}
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->actions["MOVE_RIGHT"])))
	{
		if (!this->CheckSpriteCollision(dt, "MOVE_RIGHT"))
		{
			this->player->Move(dt, 1.f, 0.f);
			if (!this->CheckViewPosition("MOVE_RIGHT"))
				this->playerView.move(1.f * 2 * this->player->getMovement()->getVelocity().x, 0.f);
		}
	}
	// Open pause menu when "Escape" is pressed
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->actions["MENU"])))
	{
		this->states->push(new MenuState(this->window, this->keys, this->states, WhichState::MENU_STATE, "../External/Config/pause_menu_buttons.cfg", Menu::PAUSE_MENU));
	}
}

void GameState::Update(const float& dt)
{
	this->UpdateMousePositions();

	this->HandleInput(dt);

	this->player->Update(dt);
}

void GameState::Render(sf::RenderTarget* target)
{
	if (!target)
		target = this->window;

	// Change the view
	target->setView(this->playerView);
	this->map->Render(target);
	this->player->Render(target);
	//target->draw(this->viewMovementArea); // Render the camera area

	// Reset the view
	target->setView(this->window->getDefaultView());
}

/* Initializes @member[actions] with the parameters in the files "game_actions.cfg"
   Format :
		Action_Name Key_Name
*/
void GameState::InitActions()
{
	std::ifstream config_file("../External/Config/game_actions.cfg");

	if (config_file.is_open())
	{
		std::string action = "";
		std::string key = "";
		while (config_file >> action >> key)
		{
			this->actions[action] = this->keys->at(key);
		}
		config_file.close();
	}

}

bool GameState::CheckSpriteCollision(const float & dt,std::string movement)
{
	// Collision are tested on a copy of the map (collidedMap). The areas that can't be crossed by the player are in red (255, 0, 0).
	sf::Vector2f sprite_position = sf::Vector2f(this->player->getSprite()->getPosition().x / this->collidedMap->getScale(), this->player->getSprite()->getPosition().y / this->collidedMap->getScale());
	sprite_position = sf::Vector2f(std::roundl(sprite_position.x), std::roundl(sprite_position.y));

	sf::Vector2f sprite_size = sf::Vector2f(this->player->getSprite()->getGlobalBounds().width / this->collidedMap->getScale(), this->player->getSprite()->getGlobalBounds().height / this->collidedMap->getScale());

	sf::Color pixel_toward_color[3];

	if (movement == "MOVE_UP")
	{
		pixel_toward_color[0] = this->collidedMap->getPixelColor(sprite_position.x + 1, sprite_position.y + sprite_size.y - 1);
		pixel_toward_color[1] = this->collidedMap->getPixelColor(sprite_position.x + sprite_size.x / 2 , sprite_position.y - 1 + sprite_size.y);
		pixel_toward_color[2] = this->collidedMap->getPixelColor(sprite_position.x - 1 + sprite_size.x, sprite_position.y - 1 + sprite_size.y);
	}
	else if (movement == "MOVE_DOWN")
	{
		pixel_toward_color[0] = this->collidedMap->getPixelColor(sprite_position.x + 1, sprite_position.y + sprite_size.y + 1);
		pixel_toward_color[1] = this->collidedMap->getPixelColor(sprite_position.x + sprite_size.x / 2, sprite_position.y + sprite_size.y + 1);
		pixel_toward_color[2] = this->collidedMap->getPixelColor(sprite_position.x - 1 + sprite_size.x, sprite_position.y + sprite_size.y + 1);
	}
	else if (movement == "MOVE_LEFT")
	{
		pixel_toward_color[0] = this->collidedMap->getPixelColor(sprite_position.x - 1, std::min(sprite_position.y + sprite_size.y, this->map->getSize().y));
		// Others are not required
		pixel_toward_color[1] = sf::Color::Green;
		pixel_toward_color[2] = sf::Color::Green;
	}
	else if (movement == "MOVE_RIGHT")
	{
		pixel_toward_color[0] = this->collidedMap->getPixelColor(sprite_position.x + sprite_size.x + 1, std::min(sprite_position.y + sprite_size.y, this->map->getSize().y));
		pixel_toward_color[1] = sf::Color::Green;
		pixel_toward_color[2] = sf::Color::Green;
	}
	for (auto &it : pixel_toward_color)
	{
		if (it == sf::Color::Red || it == sf::Color::Blue)
		{
			this->player->getMovement()->setVelocity(0, 0);
			this->player->getAnimation()->PlayAnimation(0, dt, movement);
			std::string side = movement.replace(movement.begin(), movement.begin() + 5, "");
			this->player->getAnimation()->setSide(StringToSide(side));
			return true;
		}
	}
	return false;
}

bool GameState::CheckViewPosition(std::string movement)
{
	sf::Vector2f sprite_size = sf::Vector2f(this->player->getSprite()->getGlobalBounds().width, this->player->getSprite()->getGlobalBounds().height);
	sf::Vector2f sprite_position = sf::Vector2f(std::round(this->player->getSprite()->getPosition().x), std::round(this->player->getSprite()->getPosition().y));

	sf::Vector2f view_center = sf::Vector2f(std::round(this->playerView.getCenter().x), std::round(this->playerView.getCenter().y));
	sf::Vector2f view_size = sf::Vector2f(std::round(this->playerView.getSize().x), std::round(this->playerView.getSize().y));

	if (movement == "MOVE_LEFT" || movement == "MOVE_RIGHT")
	{
		return (sprite_position.x <= this->viewLocked["LEFT"] || sprite_position.x > this->viewLocked["RIGHT"]);
	}
	else if (movement == "MOVE_DOWN" || movement == "MOVE_UP")
	{
		return (sprite_position.y <= this->viewLocked["UP"] || sprite_position.y > this->viewLocked["DOWN"]);
	}
}