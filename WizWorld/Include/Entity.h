#ifndef _ENTITY_H_
#define _ENTITY_H_

#include "MovementComponent.h"
#include "AnimationComponent.h"

class Entity
{
public:
	Entity();
	virtual ~Entity();
	virtual void move(const float& dt, const float x_motion, const float y_motion);

	virtual void update(const float &dt) = 0;
	virtual void render(sf::RenderTarget* target);

	void createSprite();
	void initializeMovementComponent(float maxVelocity, float acceleration, float deceleration);
	virtual void iniatializeAnimationComponent();
	virtual void initializeTextures();
	
	/* Getters */
	MovementComponent *getMovement() const;
	AnimationComponent *getAnimation() const;

protected:
	sf::Sprite *m_sprite;
	std::map<std::string, sf::Texture> m_textures;
	MovementComponent *m_movement;
	AnimationComponent *m_animation;
	
};

#endif //!_ENTITY_H_
