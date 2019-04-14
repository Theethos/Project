#include "Precompiled_Header.h"
#include "../Include/Macros.h"
#include "../Include/Player.h"

/* Constructor */
Player::Player(float maxVelocity, float x_pos, float y_pos, std::string config_file, std::string name, sf::Font* font, int sprite_scale) : Entity(), name(name), font(font)
{
	/* Initializers */
	createSprite();
	this->sprite->setPosition(sf::Vector2f(x_pos, y_pos));
	this->sprite->setScale(sprite_scale, sprite_scale);

	initMovementComponent(maxVelocity, 10.f, 9.f);
	iniatializeAnimationComponent(config_file);
	initName();
	// Set the sprite texture to IDLE_DOWN at the beginning
	this->animation->idleAnimation(0.05, "MOVE_DOWN");
}

/* Destructor */
Player::~Player()
{
	delete this->sprite;
	delete this->movement;
	delete this->animation;
	delete this->hitbox;
}

/* Overload of superclass function */
void Player::iniatializeAnimationComponent(std::string file_path)
{
	// Calls the superclass init
	Entity::iniatializeAnimationComponent();

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
			this->animation->addAnimation(key, texture_sheet, number_of_textures, width, height, animation_timer);
		}
		config_file.close();
	}
}

void Player::update(const float & dt)
{
	if (this->sprite && this->movement)
	{
		// Calls the decelerating phase
		this->movement->update(dt, this->sprite);
		// Update hitbox
		this->hitbox->update();
		if (this->animation)
		{
			// Sets the accurate texture depending on the sprite orientation
			// If the player moves, it will be changes after so those animations are only played if the player doesn't move
			switch (this->animation->getSide())
			{
				case AnimationSide::LEFT:
					this->animation->idleAnimation(0.005, "MOVE_LEFT");
					break;
				case AnimationSide::RIGHT:
					this->animation->idleAnimation(0.005, "MOVE_RIGHT");
					break;
				case AnimationSide::UP:
					this->animation->idleAnimation(0.005, "MOVE_UP");
					break;
				case AnimationSide::DOWN:
					this->animation->idleAnimation(0.005, "MOVE_DOWN");
					break;
				default:
					break;
			}
		}
		this->nameRendered.setPosition(this->sprite->getPosition() - sf::Vector2f((this->nameRendered.getGlobalBounds().width - this->sprite->getGlobalBounds().width) / 2, 3 * this->sprite->getScale().x + this->nameRendered.getGlobalBounds().height));
	}
}

void Player::render(sf::RenderTarget * target)
{
	Entity::render(target);
	target->draw(this->nameRendered);
}

void Player::initName()
{
	if (this->font->loadFromFile("../External/Fonts/PixieFont.ttf"))
	{
		this->nameRendered.setFont(*this->font);
		this->nameRendered.setFillColor(sf::Color::Black);
		this->nameRendered.setString(this->name);
	}
}

sf::Sprite * Player::getSprite() const
{
	return this->sprite;
}

