#ifndef ITEM_H
#define ITEM_H

#include <string>

/* Validate weapons : Wand/Staff/Magic Ring  --- Possible weapons : Bow/Sword/Hammer/Axe/Club */
					// Items																										 // Weapons
enum ItemCategories { NO_ITEM, HAT, CLOAK, CHEST, BELT, PANTS, BOOTS, GLOVE_1, GLOVE_2, NECKLESS, EARING_1, EARING_2, RING_1, RING_2, WAND, STAFF, MAGIC_RING, SHIELD };

class Item
{
public:
	Item();
	Item(std::string name, ItemCategories category);
	Item(const Item &item);
	~Item();
	Item &operator=(const Item &item);

	std::string getName() const;
	ItemCategories getCategory() const;

protected:
	std::string m_name;
	ItemCategories m_category;
};


class Weapon : public Item
{
public:
	Weapon();
	Weapon(std::string name, ItemCategories category, int damage);
	Weapon(const Weapon &weapon);
	~Weapon();
	Weapon &operator=(const Weapon &weapon);


	int getDamage() const;

private:
	int m_damage;
};



#endif // !ITEM_H

