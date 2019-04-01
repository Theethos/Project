#include "../Include/Player.h"

/* Constructor */
Player::Player(float maxVelocity, float x_pos, float y_pos) : Entity()
{
	/* Initializers */
	createSprite();
	m_sprite->setPosition(sf::Vector2f(x_pos, y_pos));

	initializeTextures();
	initializeMovementComponent(maxVelocity, 10.f, 9.f);
	iniatializeAnimationComponent();
	// Set the sprite texture to IDLE_DOWN at the beginning
	m_animation->playAnimation(1, 0, "IDLE_DOWN");
}

/* Destructor */
Player::~Player()
{
	delete m_sprite;
	delete m_movement;
	delete m_animation;
	delete m_hitbox;
}

/* Overload of superclass function */
void Player::iniatializeAnimationComponent()
{
	// Calls the superclass initializer
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
			m_animation->addAnimation(key, texture_sheet, number_of_textures, width, height, animation_timer);
		}
		config_file.close();
	}
}

void Player::update(const float & dt)
{
	if (m_sprite && m_movement)
	{
		// Calls the decelerating phase
		m_movement->update(dt, m_sprite);
		// Update hitbox
		m_hitbox->update();
		if (m_animation)
		{
			// Sets the accurate texture depending on the sprite orientation
			// If the player moves, it will be changes after so those animations are only played if the player doesn't move
			switch (m_animation->getSide())
			{
				case AnimationSide::LEFT:
					m_animation->playAnimation(m_movement->getVelocity().x, dt, "IDLE_LEFT");
					break;
				case AnimationSide::RIGHT:
					m_animation->playAnimation(m_movement->getVelocity().x, dt, "IDLE_RIGHT");
					break;
				case AnimationSide::UP:
					m_animation->playAnimation(m_movement->getVelocity().y, dt, "IDLE_UP");
					break;
				case AnimationSide::DOWN:
					m_animation->playAnimation(m_movement->getVelocity().y, dt, "IDLE_DOWN");
					break;
				default:
					break;
			}
		}
	}
}

