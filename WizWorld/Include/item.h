/* Validate weapons : Wand/Staff/Magic Ring  --- Possible weapons : Bow/Sword/Hammer/Axe/Club */

#ifndef _ITEM_H_
#define _ITEM_H_

class Item
{
public:
	Item();
	Item(std::string name, ItemCategories category);
	Item(const Item &item);
	virtual ~Item();

	Item &operator=(const Item &item);

	/* Getters */
	virtual std::string getName() const;
	virtual ItemCategories getCategory() const;
	virtual std::string showCategory() const;

protected:
	std::string m_name;
	ItemCategories m_category;
};

#endif // !_ITEM_H_

