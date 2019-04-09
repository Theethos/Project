#include "../Include/HitboxComponent.h"

HitboxComponent::HitboxComponent(sf::Sprite *sprite, const float width, const float height) : sprite(sprite)
{
	this->hitbox.setPosition(this->sprite->getPosition());
	this->hitbox.setSize(sf::Vector2f(width, height));

	this->hitbox.setFillColor(sf::Color::Transparent);
	this->hitbox.setOutlineThickness(1.f);
	this->hitbox.setOutlineColor(sf::Color::Red);
}

HitboxComponent::~HitboxComponent()
{}

void HitboxComponent::update()
{
	this->hitbox.setPosition(this->sprite->getPosition());
}

void HitboxComponent::render(sf::RenderTarget * target) const
{
	target->draw(this->hitbox);
}

bool HitboxComponent::checkCollision(const sf::FloatRect & rect)
{
	return this->hitbox.getGlobalBounds().intersects(rect);
}