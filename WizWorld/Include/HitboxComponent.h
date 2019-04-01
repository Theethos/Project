#ifndef _HITBOX_COMPONENT_H_
#define _HITBOX_COMPONENT_H_

#define _REQUIRE_SFML_
	#include "Macro_Include.h"
#undef _REQUIRE_SFML_

class HitboxComponent
{
public:
	HitboxComponent(sf::Sprite *sprite, const float width, const float height);
	virtual ~HitboxComponent();

	void update();
	void render(sf::RenderTarget* target) const;

	bool checkCollision(const sf::FloatRect &rect);
private:
	sf::RectangleShape m_hitbox;
	sf::Sprite *m_sprite;
};

#endif // !_HITBOX_COMPONENT_H_

