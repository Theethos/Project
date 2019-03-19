/* Validate weapons : Wand/Staff/Magic Ring  --- Possible weapons : Bow/Sword/Hammer/Axe/Club */

#ifndef _ITEM_H_
#define _ITEM_H_

/*
 * ==================================================
 * ================= Class Item =====================
 * ==================================================
 */

class Item
{
public:
	/*=== Constructors/Destructor ===*/

	Item();
	Item(std::string name, ItemCategories category);
	Item(const Item &item);
	virtual ~Item();

	/*=== Operator overload ===*/

	Item &operator=(const Item &item);

	/*=== Getters ===*/
	
	/* Name */
	virtual std::string getName() const;
	/* Category */
	virtual ItemCategories getCategory() const;
	/* Category (string not enum [for display]) */
	virtual std::string showCategory() const;

protected:

	std::string m_name;
	ItemCategories m_category;
};

#endif // !_ITEM_H_

