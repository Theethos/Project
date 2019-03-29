#ifndef _ENTITY_H_
#define _ENTITY_H_

#define _REQUIRE_SFML_
	#include "Macro_Include.h"
#undef _REQUIRE_SFML_

class Entity
{
public:
	Entity(double speed, sf::Texture *texture);
	virtual ~Entity();
	/* Move the entity; x and y are in {-1, 0, 1} */
	virtual void move(const double& dt, const double x_motion, const double y_motion);

	virtual void update(const double &dt);
	virtual void render(sf::RenderTarget* target);

	void createSprite(sf::Texture *texture);

protected:
	sf::Sprite *m_sprite;
	sf::Texture *m_texture;
	double m_speed;
};

#endif //!_ENTITY_H_
