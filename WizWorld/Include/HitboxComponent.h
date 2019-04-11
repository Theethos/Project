#ifndef _HITBOX_COMPONENT_H_
#define _HITBOX_COMPONENT_H_

class HitboxComponent
{
public:
	HitboxComponent(sf::Sprite *sprite, const float width, const float height);
	virtual ~HitboxComponent();

	void update();
	void render(sf::RenderTarget* target) const;

	bool checkCollision(const sf::FloatRect &rect);
private:
	sf::RectangleShape hitbox;
	sf::Sprite *sprite;
};

#endif // !_HITBOX_COMPONENT_H_

