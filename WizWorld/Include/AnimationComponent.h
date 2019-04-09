#ifndef _ANIMATION_COMPONENT_H_
#define _ANIMATION_COMPONENT_H_

#define _REQUIRE_SFML_
	#include "Macro_Include.h"
#undef _REQUIRE_SFML_

/* Enum to describe the orientation of a sprite */
enum class AnimationSide {LEFT, RIGHT, DOWN, UP};

class AnimationComponent
{
private:
	/* Private struct that stores one animation */
	struct Animation
	{
		sf::Texture *textureSheet;
		// Associated sprite
		sf::Sprite *sprite;
		// Area of the texture sheet that will be rendered
		sf::IntRect currentRect;
		// Number of image in the texture sheet
		int numberOfTextures;
		// Time between two frames of the animation 
		float animationTimer;
		// Time spend between last call to this animation
		float timer;

		/* Constructor */
		Animation() : textureSheet(nullptr), sprite(nullptr), currentRect(0, 0, 0, 0), numberOfTextures(0), animationTimer(0),
			timer(0)
		{}

		/* Initializes the animation during "addAnimation()" in the AnimationComponent class */
		void init(sf::Texture *textureSheet, sf::Sprite *sprite, int numberOfTextures, float animationTimer, int width, int height)
		{
			this->textureSheet = textureSheet;
			this->sprite = sprite;
			this->numberOfTextures = numberOfTextures; 
			this->animationTimer = animationTimer;
			this->currentRect = sf::IntRect(0, 0, width/numberOfTextures, height);
		}

		void play(const float & velocity, const float &dt)
		{
			// Update the timer
			// Plays the animation faster if the entity's velocity is greater than 1
			if (std::abs(velocity) < 1)
				this->timer += dt;
			else
				this->timer += dt * std::abs(velocity);
			// If their has been enough time since the last frame
			if (this->timer >= this->animationTimer)
			{
				// Update sprite's texture
				this->sprite->setTexture(*this->textureSheet, true);
				this->sprite->setTextureRect(this->currentRect);
				
				// Reset timer
				this->timer = 0;

				// Moving on to the next frame of the animation
				this->currentRect.left += this->currentRect.width;

				// And if it was the last one, it goes back to first frame
				if (this->currentRect.left == this->currentRect.width * this->numberOfTextures)
				{
					reset();
				}
			}
		}
		// Reset the animation
		void reset()
		{
			this->currentRect.left = 0;
			this->timer = 0;
		}
	};

public:
	AnimationComponent(sf::Sprite *sprite);
	virtual ~AnimationComponent();

	void addAnimation(const std::string key, sf::Texture *textureSheet, int numberOfTextures, int width, int height, float animationTimer = 0.5);

	void playAnimation(const float & velocity, const float & dt, const std::string animation);
	void resetAnimation(const std::string animation);

	/* Getter */
	AnimationSide getSide() const;

	/* Setter */
	void setSide(const AnimationSide side);

private:
	// Map of animation
	std::map<std::string, Animation> animation;
	// Sprite on which to play the animation
	sf::Sprite *associatedSprite;
	// Orientation of this sprite (to play the right animation)
	AnimationSide side;
};



#endif // !_ANIMATION_COMPONENT_H_
