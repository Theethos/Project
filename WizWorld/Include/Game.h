#ifndef _GAME_H_
#define _GAME_H_

class Game
{
public:
	Game();
	virtual ~Game();

	/* It is the main fonction (this is where the magic happens) */
	void run();

private:
	/*=== Attributes ===*/
	sf::RenderWindow m_window;
	sf::Event m_event;

	/*=== Private methods ===*/

	void update();
	void updateEvents();
	void render();
	/* Initializes @member[window] with the parameters in the files "window.cfg" */
	void initializeWindow();
};

#endif // !_GAME_H_
