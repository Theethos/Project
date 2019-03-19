#ifndef _WINDOW_H_
#define _WINDOW_H_

#include "../Include/Macros_Includes.h"

#include "../Include/Character.h"
#include "../Include/Item.h"
#include "../Include/Weapon.h"
#include "../Include/Armor.h"
#include "../Include/Window.h"


class Window
{
public:
	Window();
	virtual ~Window();

	void update();
	//void render();

	/*=== Getters ===*/

	bool isOpen();

private:
	sf::RenderWindow m_window;
	int m_height;
	int m_width;
	std::string m_title;

};

#endif // !_WINDOW_H_
