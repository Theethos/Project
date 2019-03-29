#include "../Include/Player.h"

Player::Player(double speed, double x_pos, double y_pos, sf::Texture *texture) : Entity(speed, texture)
{
	createSprite(texture);
	m_sprite->setScale(sf::Vector2f(100 / m_sprite->getGlobalBounds().width, 100 / m_sprite->getGlobalBounds().height));
	m_sprite->setPosition(sf::Vector2f(x_pos, y_pos));
}


Player::~Player()
{
}


