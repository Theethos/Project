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
		sf::Texture *m_textureSheet;
		// Associated sprite
		sf::Sprite *m_sprite;
		// Area of the texture sheet that will be rendered
		sf::IntRect m_currentRect;
		// Number of image in the texture sheet
		int m_numberOfTextures;
		// Time between two frames of the animation 
		float m_animationTimer;
		// Time spend between last call to this animation
		float m_timer;
		// Boolean to pause the animation
		bool m_pause;

		/* Constructor */
		Animation() : m_textureSheet(nullptr), m_sprite(nullptr), m_currentRect(0, 0, 0, 0), m_numberOfTextures(0), m_animationTimer(0),
			m_timer(0), m_pause(false)
		{}

		/* Initializes the animation during "addAnimation()" in the AnimationComponent class */
		void initialize(sf::Texture *textureSheet, sf::Sprite *sprite, int numberOfTextures, float animationTimer, int width, int height)
		{
			m_textureSheet = textureSheet;
			m_sprite = sprite;
			m_numberOfTextures = numberOfTextures; 
			m_animationTimer = animationTimer;
			m_currentRect = sf::IntRect(0, 0, width/numberOfTextures, height);
		}

		void update(const float &dt)
		{
			// Update timer if is it not paused
			if (!m_pause)
				m_timer += dt;
			// If their has been enough time since the last frame
			if (m_timer >= m_animationTimer)
			{
				// Update sprite's texture
				m_sprite->setTexture(*m_textureSheet, true);
				m_sprite->setTextureRect(m_currentRect);
				
				// Reset timer
				m_timer = 0;

				// Moving on to the next frame of the animation
				m_currentRect.left += m_currentRect.width;

				// And if it was the last one, it goes back to first frame
				if (m_currentRect.left == m_currentRect.width * m_numberOfTextures)
				{
					reset();
				}
			}
		}
		// Pause the animation
		void pause()
		{
			m_pause = true;
			m_timer = 0;
		}
		// Reset the animation
		void reset()
		{
			m_currentRect.left = 0;
			m_timer = 0;
			m_pause = false;
		}
	};

public:
	AnimationComponent(sf::Sprite *sprite);
	virtual ~AnimationComponent();

	void addAnimation(const std::string key, sf::Texture *textureSheet, int numberOfTextures, int width, int height, float animationTimer = 0.5);

	void playAnimation(const float & dt, const std::string animation);
	void pauseAnimation(const std::string animation);
	void resetAnimation(const std::string animation);

	/* Getter */
	AnimationSide getSide() const;

	/* Setter */
	void setSide(const AnimationSide side);

private:
	// Map of animation
	std::map<std::string, Animation> m_animation;
	// Sprite on which to play the animation
	sf::Sprite *m_associatedSprite;
	// Orientation of this sprite (to play the right animation)
	AnimationSide m_side;
};



#endif // !_ANIMATION_COMPONENT_H_
