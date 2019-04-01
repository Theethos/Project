#include "../Include/AnimationComponent.h"

/* Constructor */
AnimationComponent::AnimationComponent(sf::Sprite *sprite) : m_associatedSprite(sprite), m_side(AnimationSide::DOWN)
{}

/* Destructor */
AnimationComponent::~AnimationComponent()
{
	for (auto &it : m_animation)
	{
		// Delete all texture sheet
		delete it.second.m_textureSheet;
		it.second.m_textureSheet = nullptr;
	}
	m_animation.clear();
}

/* Functions */
void AnimationComponent::addAnimation(const std::string key, sf::Texture * textureSheet, int numberOfTextures, int width, int height, float animationTimer)
{
	// Create and set a new animation with a "key"
	m_animation[key].initialize(textureSheet, m_associatedSprite, numberOfTextures, animationTimer, width, height);
}

void AnimationComponent::playAnimation(const float & dt, const std::string animation)
{
	m_animation[animation].update(dt);
}

void AnimationComponent::pauseAnimation(const std::string animation)
{
	m_animation[animation].pause();
}

void AnimationComponent::resetAnimation(const std::string animation)
{
	m_animation[animation].reset();
}

void AnimationComponent::setSide(const AnimationSide side)
{
	m_side = side;
}

AnimationSide AnimationComponent::getSide() const
{
	return m_side;
}
