#ifndef _ENTITY_H_
#define _ENTITY_H_

#define _REQUIRE_SFML_
	#include "Macro_Include.h"
#undef _REQUIRE_SFML_

class Entity
{
public:
	Entity();
	Entity(float speed, float x_shape, float y_shape);
	virtual ~Entity();
	/* Move the entity; x and y are in {-1, 0, 1} */
	virtual void move(const float& dt, const float x_motion, const float y_motion);

	virtual void update(const float &dt);
	virtual void render(sf::RenderTarget* target);

protected:
	sf::RectangleShape m_shape;
	float m_speed;
};

#endif //!_ENTITY_H_
