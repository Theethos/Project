#ifndef _ANIMATION_COMPONENT_H_
#define _ANIMATION_COMPONENT_H_

class AnimationComponent
{
private:
	// Private struct that stores one animation
	struct Animation
	{
		sf::Texture *textureSheet;
		sf::Sprite *sprite;
		// Area of the texture sheet that will be rendered
		sf::IntRect currentRect;
		// Number of image in the texture sheet
		int numberOfTextures;
		// Time between two frames of the animation 
		float animationTimer;
		// Time spend between last call to this animation
		float timer;

		// Constructor
		Animation() :
		textureSheet(nullptr), 
		sprite(nullptr),
		currentRect(0, 0, 0, 0), 
		numberOfTextures(0), 
		animationTimer(0),
		timer(0)
		{}

		// Functions
		// Initializes the animation during "AddAnimation()" in the AnimationComponent class
		void Init(sf::Texture *textureSheet, sf::Sprite *sprite, int numberOfTextures, float animationTimer, int width, int height)
		{
			this->textureSheet = textureSheet;
			this->sprite = sprite;
			this->numberOfTextures = numberOfTextures; 
			this->animationTimer = animationTimer;
			this->currentRect = sf::IntRect(0, 0, width/numberOfTextures, height);
		}

		void Play(const float & velocity, const float &dt)
		{
			// Updates the timer
			// Plays the animation faster if the entity's velocity is greater than 1
			if (std::abs(velocity) < 1 || this->numberOfTextures <= 4)
				this->timer += dt;
			else
				this->timer += dt * std::abs(velocity);
			
			// If there has been enough time since the last frame
			if (this->timer >= this->animationTimer)
			{
				// Updates sprite's texture
				this->sprite->setTexture(*this->textureSheet, true);
				this->sprite->setTextureRect(this->currentRect);
				
				// Resets timer
				this->timer = 0;

				// Moves on to the next frame of the animation
				this->currentRect.left += this->currentRect.width;

				// And if it was the last one, it goes back to first frame
				if (this->currentRect.left == this->currentRect.width * this->numberOfTextures)
				{
					Reset();
				}
			}
		}
		
		void Reset()
		{
			this->currentRect.left = 0;
			this->timer = 0;
		}
		// Set the texture to the first of the sprite sheet -> idle
		void Idle(const float &dt)
		{
			this->timer += dt;

			if (this->timer >= this->animationTimer)
			{
				this->sprite->setTexture(*this->textureSheet, true);
				this->sprite->setTextureRect(sf::IntRect(this->currentRect.width, 0, this->currentRect.width, this->currentRect.height));
				// Reset timer
				this->timer = 0;
			}
		}
	};

public:
	// Constructor
	AnimationComponent(sf::Sprite *sprite);
	// Destructor
	virtual ~AnimationComponent();

	// Functions
	void AddAnimation(const std::string key, sf::Texture *textureSheet, int numberOfTextures, int width, int height, float animationTimer = 0.5);
	void PlayAnimation(const float & velocity, const float & dt, const std::string animation);
	void ResetAnimation(const std::string animation);
	void IdleAnimation(const float &dt, const std::string animation);

	// Getters
	AnimationSide getSide() const;
	sf::Texture* getTexture(std::string animation);

	// Setter
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
