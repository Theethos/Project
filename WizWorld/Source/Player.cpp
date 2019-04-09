#include "../Include/Player.h"

/* Constructor */
Player::Player(float maxVelocity, float x_pos, float y_pos) : Entity()
{
	/* Initializers */
	createSprite();
	this->sprite->setPosition(sf::Vector2f(x_pos, y_pos));

	initMovementComponent(maxVelocity, 10.f, 9.f);
	iniatializeAnimationComponent();
	// Set the sprite texture to IDLE_DOWN at the beginning
	this->animation->playAnimation(1, 0, "IDLE_DOWN");
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
void Player::iniatializeAnimationComponent()
{
	// Calls the superclass initr
	Entity::iniatializeAnimationComponent();

	/*	Loads the textures from a file
		Format : 
			key  path  number_of_frames_in_the_animation  width_of_the_texture_sheet  height  time_between_two_frames */
	std::ifstream config_file("../External/Config/player_sprites_sheet.cfg");

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
					this->animation->playAnimation(this->movement->getVelocity().x, dt, "IDLE_LEFT");
					break;
				case AnimationSide::RIGHT:
					this->animation->playAnimation(this->movement->getVelocity().x, dt, "IDLE_RIGHT");
					break;
				case AnimationSide::UP:
					this->animation->playAnimation(this->movement->getVelocity().y, dt, "IDLE_UP");
					break;
				case AnimationSide::DOWN:
					this->animation->playAnimation(this->movement->getVelocity().y, dt, "IDLE_DOWN");
					break;
				default:
					break;
			}
		}
	}
}

