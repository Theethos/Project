#include "Precompiled_Header.h"
#include "../Include/Macros.h"
#include "../Include/AnimationComponent.h"

// Constructor
AnimationComponent::AnimationComponent(sf::Sprite *sprite) : 
associatedSprite(sprite), 
side(AnimationSide::DOWN)
{}
// Destructor
AnimationComponent::~AnimationComponent()
{
	for (auto &it : this->animation)
	{
		// Delete all texture sheet
		delete it.second.textureSheet;
		it.second.textureSheet = nullptr;
	}
	this->animation.clear();
}

// Functions
void AnimationComponent::AddAnimation(const std::string key, sf::Texture * textureSheet, int numberOfTextures, int width, int height, float animationTimer)
{
	// Create and set a new animation with a "key"
	this->animation[key].Init(textureSheet, this->associatedSprite, numberOfTextures, animationTimer, width, height);
}

void AnimationComponent::PlayAnimation(const float & velocity, const float & dt, const std::string animation)
{
	this->animation[animation].Play(velocity, dt);
}

void AnimationComponent::ResetAnimation(const std::string animation)
{
	this->animation[animation].Reset();
}

void AnimationComponent::IdleAnimation(const float &dt, const std::string animation)
{
	this->animation[animation].Idle(dt);
}

// Getters
AnimationSide AnimationComponent::getSide() const
{
	return this->side;
}

sf::Texture * AnimationComponent::getTexture(std::string animation)
{
	if (this->animation.count(animation))
		return this->animation[animation].textureSheet;
}

// Setter
void AnimationComponent::setSide(const AnimationSide side)
{
	this->side = side;
}
