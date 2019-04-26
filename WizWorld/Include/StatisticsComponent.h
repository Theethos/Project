#ifndef STATISTICS_COMPONENT_H
#define STATISTICS_COMPONENT_H

class StatisticsComponent
{
public:
	// Constructor
	StatisticsComponent();
	// Destructor
	virtual ~StatisticsComponent();

	// Internal static struct
	static struct HealthPoints
	{
		// Value of HP added every level
		const long _increment = 15;
		long _currentHP;
		// Player gains HP every level (increment/level)
		long _levelHP;
		// HP gained with characteristics
		long _statisticsHP;
		// HP gained with stuff
		long _equipmentHP;

		// Constructor
		inline HealthPoints(long currentHP = 150, long levelHP = 150, long statisticsHP = 0, long equipmentHP = 0) :
		_currentHP(currentHP),
		_levelHP(levelHP),
		_statisticsHP(statisticsHP),
		_equipmentHP(equipmentHP) {}
	};
	static struct Experience
	{
		// Value of the increase of _next every level
		const float _increment = 1.405;
		int _level;
		long long _current;
		long long _next;

		// Constructor
		Experience(int level = 1, long long current = 0, long long next = 150) :
		_level(level),
		_current(current),
		_next(next) {}
	};

	// Functions
	void addExp(long long amount);
	void removeExp(long long amount);
	void addHp(long amount);
	void removeHp(long amount);

	// Getters
	inline const long &getCurrentHP() const { return _healthPoints._currentHP; }
	inline const long &getMaxHP() const { return _healthPoints._levelHP + _healthPoints._statisticsHP + _healthPoints._equipmentHP; }
	inline const int& getLevel() const { return _experience._level; }
	inline const long long& getCurrentLevelExp() const { return _experience._current; }
	inline const long long& getNextLevelExp() const { return _experience._next; }

private:
	HealthPoints _healthPoints;
	Experience _experience;

	long long getPreviousNext();
};

#endif // !STATISTICS_COMPONENT_H

