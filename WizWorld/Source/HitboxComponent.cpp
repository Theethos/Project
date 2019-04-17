#include "Precompiled_Header.h"
#include "../Include/Macros.h"
#include "../Include/HitboxComponent.h"

// Constructor
HitboxComponent::HitboxComponent(sf::Sprite *sprite, const float width, const float height) : 
sprite(sprite)
{
	this->hitbox.setPosition(this->sprite->getPosition());
	this->hitbox.setSize(sf::Vector2f(width, height));

	this->hitbox.setFillColor(sf::Color::Transparent);
	this->hitbox.setOutlineThickness(1.f);
	this->hitbox.setOutlineColor(sf::Color::Red);
}
// Destructor
HitboxComponent::~HitboxComponent()
{}

// Functions
void HitboxComponent::Update()
{
	this->hitbox.setPosition(this->sprite->getPosition());
}

void HitboxComponent::Render(sf::RenderTarget * target) const
{
	target->draw(this->hitbox);
}