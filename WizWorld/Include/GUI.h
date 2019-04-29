#ifndef GUI_H
#define GUI_H

#include "Player.h"

class GUI
{
public:
	GUI(sf::RenderWindow &window, Player & player);
	virtual ~GUI();

	// Functions
	virtual void Update(const float &dt) = 0;
	virtual void Render(sf::RenderTarget *target) = 0;
	// Function which behavior has to defined in UpdatePosition()
	virtual void Move();
	inline void Toggle() { (_visible ? _visible = false : _visible = true); }

	// token to control the number of moving GUI (Drag&Drop) : only one at a time
	static bool _token;

private:
	// List of all instances -> required to check collisions between modules.
	static std::list<GUI*> _instances;
protected:
	bool _visible;
	bool _move;
	sf::Vector2f _offset;

	sf::RenderWindow &_window;
	sf::Font _font;

	// Entity related to
	Player &_player;

	// Global
	sf::RectangleShape _globalShape;
	sf::Color _globalColor;
	sf::Color _globalColorText;

	// Private functions
	// Defines the behavior to use when function Move() is called (When user use Drag&Drop on the GUI module)
	virtual void UpdatePosition(const sf::Vector2f &mousePos) = 0;
	// Get the most likely position of the GUI module if it collides with an other
	virtual const sf::Vector2f getNewPosition(const sf::FloatRect & intersect) const;
};

#endif // !GUI_H

