#include "../Include/Macro_Include.h"
#include "../Include/Character.h"


/* Constructors */
Character::Character() : m_name("Mickael"), m_sexe(Sexe::MALE), m_hair{ HairColor::DARK, HairStyle::SHORT }, m_level{ 1, 0, 300 }, m_healthPoints{ 100, 100, 0, 0 }, m_inventory()
{}

Character::Character(std::string name, Sexe sexe, HairColor color, HairStyle style)
					: m_name(name), m_sexe(sexe), m_hair{ color, style }, m_level{ 1, 0, 300 }, 
					  m_healthPoints{ 100, 100, 0, 0 }, m_inventory()
{}

/* Destructor */
Character::~Character() 
{}

/* Displays informations about the character */
void Character::introduce() const
{
	std::cout << "Hello, my name is " << m_name << ". I am level " << m_level.level << " and I have " << m_healthPoints.currentHealthPoints << "/" << m_healthPoints.characteristicHealthPoint + m_healthPoints.equipmentHealthPoints + m_healthPoints.levelHealthPoints << " health points." << std::endl;
}

/* Adds EXPValue to the character's current EXP */
void Character::gainEXP(long long EXPValue)
{
	std::cout << m_name << " gains " << std::to_string(EXPValue) << " EXP! " << GENDER(m_sexe, "His", "Her") << " current EXP : " << m_level.currentLevelEXP << "/" << m_level.nextLevelEXP << "." << std::endl << std::endl;
	
	m_level.currentLevelEXP += EXPValue;
	while (m_level.currentLevelEXP >= m_level.nextLevelEXP)
	{
		if (m_level.level < 50) // Level max is 50 (== 5 148 376 331 EXP)
		{
			m_level.level += 1;
			
			std::cout << m_name << " levels up ! " << GENDER(m_sexe, "He", "She") << " is now level " << m_level.level;
			
			// Each level, characters need 0.405 more EXP to level up
			m_level.nextLevelEXP += (long long)(m_level.nextLevelEXP * 0.405); 
			// Each level, characters gain 50 "native" HP
			m_healthPoints.levelHealthPoints += 50; 
			
			std::cout << " (" << MIN(m_level.currentLevelEXP, m_level.nextLevelEXP, m_level.currentLevelEXP, m_level.nextLevelEXP) << "/" << m_level.nextLevelEXP << ")" << std::endl;
		}
		// Amount of EXP already at max
		else 
		{
			std::cout << m_name << " is already level " << m_level.level;
			
			m_level.currentLevelEXP = m_level.nextLevelEXP;
			
			std::cout << " (" << m_level.currentLevelEXP << "/" << m_level.nextLevelEXP << ")" << std::endl;
			// Goes out the while loop
			break;
		}
	}
}

/* Removes DamageValue to the character's health points */
void Character::receiveDamage(int damageValue)
{
	std::cout << m_name << " loses " << damageValue << " health points." << std::endl;
	
	m_healthPoints.currentHealthPoints -= damageValue;
	// Check that HPs dont go below 0
	if (m_healthPoints.currentHealthPoints < 0)
	{
		m_healthPoints.currentHealthPoints = 0;
	}
}

/* Attacks the target with the weapon that has the higher damages */
void Character::hitWithWeapon(Character &target) const
{
	// Select the best weapon 
	Weapon *weapon = MAX(m_inventory.getWeapon_1()->getDamage(), m_inventory.getWeapon_2()->getDamage(), m_inventory.getWeapon_1(), m_inventory.getWeapon_2());
	std::cout << m_name << " hits " << target.m_name << " with " << GENDER(m_sexe, "his ", "her ") << weapon->getName() << "." << std::endl;

	target.receiveDamage(weapon->getDamage());
}

/* Puts an item in the character's inventory if it is not full */
void Character::pickUpItem(Item * item)
{
	std::cout << m_name << " picks up \"" << item->getName() << "\"." << std::endl;
	
	m_inventory.setBag(item);
}

/* Equips an item depending on its category */
void Character::equipItem(Item * item)
{
	std::cout << m_name << " equips \"" << item->getName() << "\"." << std::endl;
	
	if (item->getCategory() == ItemCategories::PRIMARY_WEAPON)
		m_inventory.setWeapon_1(dynamic_cast<Weapon*>(item));
	else if (item->getCategory() == ItemCategories::SECONDARY_WEAPON)
		m_inventory.setWeapon_2(dynamic_cast<Weapon*>(item));
	else
		m_inventory.setStuff(dynamic_cast<Armor*>(item));
}

/* DEBUG FUNCTION : just display what is inside the character's inventory */
void Character::displayInventory() const
{
	std::cout << m_name << "'s inventory : " << std::endl << std::endl << "Bag : [";

	// Display items in bag 
	for (int i = 0; i < m_inventory.getSize(); i++)
	{
		if (m_inventory.getBag()[i])
			std::cout << m_inventory.getBag()[i]->getName() << "//";
		else
			std::cout << "..." << "//";
	}

	std::cout << "]" << std::endl << "      [";

	// Display the item's category
	for (int i = 0; i < m_inventory.getSize(); i++)
	{
		if (m_inventory.getBag()[i] != nullptr)
		{
			std::cout << m_inventory.getBag()[i]->showCategory();

			for (int j = 0; j < (m_inventory.getBag()[i]->getName().size() - m_inventory.getBag()[i]->showCategory().size() > 0) ? (m_inventory.getBag()[i]->getName().size() - m_inventory.getBag()[i]->showCategory().size()) : 0; j++)
			{
				std::cout << " ";
			}
			std::cout << "//";
		}
		else
			std::cout << "..." << "//";
	}

	std::cout << "]" << std::endl << std::endl << "Stuff : [";
	
	for (int i = 0; i < static_cast<int>(ArmorCategories::RING_2); i++)
	{
		if (m_inventory.getStuff()[i] != nullptr)
			std::cout << m_inventory.getStuff()[i]->getName() << "//";
		else
			std::cout << "..." << "//";
	}
	std::cout << "]" << std::endl << "        [";
	for (int i = 0; i < static_cast<int>(ArmorCategories::RING_2); i++)
	{
		if (m_inventory.getStuff()[i] != nullptr)
		{
			std::cout << m_inventory.getStuff()[i]->showCategory();
			for (int j = 0; j < (m_inventory.getStuff()[i]->getName().size() - m_inventory.getStuff()[i]->showCategory().size() > 0) ? (m_inventory.getStuff()[i]->getName().size() - m_inventory.getStuff()[i]->showCategory().size()) : 0; j++)
			{
				std::cout << " ";
			}
			std::cout << "//";
		}
		else
			std::cout << "..." << "//";
	}
	std::cout << "]" << std::endl << std::endl << "Weapon : - Primary weapon : ";
	if (m_inventory.getWeapon_1() != nullptr)
		std::cout << m_inventory.getWeapon_1()->getName() << " (" << m_inventory.getWeapon_1()->showCategory() << ", " << m_inventory.getWeapon_1()->getDamage() << PLURAL(m_inventory.getWeapon_1()->getDamage(), " damages)", " damage)") << std::endl;
	else
		std::cout << " None" << std::endl;
	if (m_inventory.getWeapon_2() != nullptr)
		std::cout << "         - Secondary weapon : " << m_inventory.getWeapon_2()->getName() << " (" << m_inventory.getWeapon_2()->showCategory() << ", " << m_inventory.getWeapon_2()->getDamage() << PLURAL(m_inventory.getWeapon_2()->getDamage(), " damages)", " damage)") << std::endl << std::endl;
	else
		std::cout << " None" << std::endl << std::endl;
}

std::string Character::getName() const
{
	std::cout << "Your character is called " << m_name << std::endl;
	return m_name;
}

Sexe Character::getSexe() const
{
	std::cout << m_name << " is a ";
	std::cout << GENDER(m_sexe, "man ", "woman ") << std::endl;
	return m_sexe;
}

int Character::getHealthPoints() const
{
	std::cout << m_name << " has " << m_healthPoints.currentHealthPoints << "/" << m_healthPoints.characteristicHealthPoint + m_healthPoints.equipmentHealthPoints + m_healthPoints.levelHealthPoints << " health points." << std::endl;
	return m_healthPoints.currentHealthPoints;
}

int Character::getLevel() const
{
	std::cout << m_name << " is level " << m_level.level << ". ";
	std::cout << GENDER(m_sexe, "his", "her") << "experience is " << m_level.currentLevelEXP << "/" << m_level.nextLevelEXP << std::endl;
	return m_level.level;
}

Inventory* Character::getInventory()
{
	return &(this->m_inventory);
}

void Character::setName(std::string name)
{
	std::cout << m_name << " will be called " << name << " from now." << std::endl;
	m_name = name;
}

void Character::setSexe(Sexe sexe)
{
	std::cout << m_name << " is now a ";
	std::cout << GENDER(m_sexe, "man ", "woman ") << std::endl;
	m_sexe = sexe;
}

void Character::setHair(HairColor color, HairStyle style)
{
	m_hair.color = color;
	m_hair.style = style;
}
