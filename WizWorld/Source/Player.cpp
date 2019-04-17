#include "Precompiled_Header.h"
#include "../Include/Macros.h"
#include "../Include/Player.h"

// Constructor 
Player::Player(float maxVelocity, float x_pos, float y_pos, std::string config_file, std::string name, sf::Font* font, int sprite_scale) :
Entity(), name(name), font(font)
{

	InitSprite();
	this->sprite->setPosition(sf::Vector2f(x_pos, y_pos));
	this->sprite->setScale(sprite_scale, sprite_scale);

	InitMovementComponent(maxVelocity, 10.f, 9.f);
	InitAnimationComponent(config_file);
	InitName();
	
	// Set the sprite texture to IDLE_DOWN at the beginning
	this->animation->IdleAnimation(0.05, "MOVE_DOWN");
}
// Destructor
Player::~Player()
{
	delete this->sprite;
	delete this->movement;
	delete this->animation;
	delete this->hitbox;
}

//Functions
void Player::Update(const float & dt)
{
	if (this->sprite && this->movement)
	{
		// Calls the decelerating phase
		this->movement->Update(dt, this->sprite);
		// Update hitbox
		this->hitbox->Update();
		if (this->animation)
		{
			// Sets the accurate texture depending on the sprite orientation
			// If the player moves, it will be changes after so those animations are only played if the player doesn't move
			switch (this->animation->getSide())
			{
				case AnimationSide::LEFT:
					this->animation->IdleAnimation(0.005, "MOVE_LEFT");
					break;
				case AnimationSide::RIGHT:
					this->animation->IdleAnimation(0.005, "MOVE_RIGHT");
					break;
				case AnimationSide::UP:
					this->animation->IdleAnimation(0.005, "MOVE_UP");
					break;
				case AnimationSide::DOWN:
					this->animation->IdleAnimation(0.005, "MOVE_DOWN");
					break;
				default:
					break;
			}
		}
		this->nameRendered.setPosition(this->sprite->getPosition() - sf::Vector2f((this->nameRendered.getGlobalBounds().width - this->sprite->getGlobalBounds().width) / 2, 3 * this->sprite->getScale().x + this->nameRendered.getGlobalBounds().height));
	}
}

void Player::Render(sf::RenderTarget * target)
{
	Entity::Render(target);
	target->draw(this->nameRendered);
}

void Player::InitAnimationComponent(std::string file_path)
{
	// Calls the superclass Init
	Entity::InitAnimationComponent();

	/*	Loads the textures from a file
		Format : 
			key  path  number_of_frames_in_the_animation  width_of_the_texture_sheet  height  time_between_two_frames */
	std::ifstream config_file(file_path);

	if (config_file.is_open())
	{
		std::string key, path;
		int number_of_textures, width, height;
		float animation_timer;

		while (config_file >> key >> path >> number_of_textures >> width >> height >> animation_timer)
		{
			// Loads appropriate texture
			sf::Texture *texture_sheet = new sf::Texture;
			texture_sheet->loadFromFile(path);
			// Add it to the animation component
			this->animation->AddAnimation(key, texture_sheet, number_of_textures, width, height, animation_timer);
		}
		config_file.close();
	}
}

void Player::InitName()
{
	this->nameRendered.setFont(*this->font);
	this->nameRendered.setFillColor(sf::Color::Black);
	this->nameRendered.setString(this->name);
	this->nameRendered.setCharacterSize(16);
}

// Getter
sf::Sprite * Player::getSprite() const
{
	return this->sprite;
}

