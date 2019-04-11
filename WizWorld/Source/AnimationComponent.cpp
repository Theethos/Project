#include "../Include/Precompiled_Header.h"
#include "../Include/Macros.h"
#include "../Include/AnimationComponent.h"

/* Constructor */
AnimationComponent::AnimationComponent(sf::Sprite *sprite) : associatedSprite(sprite), side(AnimationSide::DOWN)
{}

/* Destructor */
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

/* Functions */
void AnimationComponent::addAnimation(const std::string key, sf::Texture * textureSheet, int numberOfTextures, int width, int height, float animationTimer)
{
	// Create and set a new animation with a "key"
	this->animation[key].init(textureSheet, this->associatedSprite, numberOfTextures, animationTimer, width, height);
}

void AnimationComponent::playAnimation(const float & velocity, const float & dt, const std::string animation)
{
	this->animation[animation].play(velocity, dt);
}

void AnimationComponent::resetAnimation(const std::string animation)
{
	this->animation[animation].reset();
}

void AnimationComponent::idleAnimation(const float &dt, const std::string animation)
{
	this->animation[animation].idle(dt);
}

void AnimationComponent::setSide(const AnimationSide side)
{
	this->side = side;
}

AnimationSide AnimationComponent::getSide() const
{
	return this->side;
}

sf::Texture * AnimationComponent::getTexture(std::string animation)
{
	return this->animation[animation].textureSheet;
}
