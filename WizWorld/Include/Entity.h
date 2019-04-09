#ifndef _ENTITY_H_
#define _ENTITY_H_

#include "HitboxComponent.h"
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
	void initMovementComponent(float maxVelocity, float acceleration, float deceleration);
	virtual void iniatializeAnimationComponent();
	virtual void initTextures();

	/* Getters */
	MovementComponent *getMovement() const;
	AnimationComponent *getAnimation() const;

protected:
	sf::Sprite *sprite;
	std::map<std::string, sf::Texture> textures;
	MovementComponent *movement;
	AnimationComponent *animation;
	HitboxComponent *hitbox;
};

#endif //!_ENTITY_H_
