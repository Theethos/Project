#include "Precompiled_Header.h"
#include "../Include/Macros.h"
#include "../Include/StatisticsComponent.h"

// Constructor
StatisticsComponent::StatisticsComponent()
{}
// Destructor
StatisticsComponent::~StatisticsComponent()
{}

void StatisticsComponent::addExp(long long amount)
{
	_experience._current += amount;
	while (_experience._current >= _experience._next)
	{
		if (_experience._level < 50)
		{
			_experience._level += 1;
			_experience._next *= _experience._increment;
			_healthPoints._levelHP += _healthPoints._increment;
			_healthPoints._currentHP = getMaxHP();
		}
		else // Level max
		{
			_experience._current = _experience._next;
			break;
		}
	}
}

void StatisticsComponent::removeExp(long long amount)
{
	_experience._current -= amount;
	long long previousNext = getPreviousNext();
	while (_experience._current < previousNext)
	{
		if (_experience._level > 1)
		{
			_experience._level -= 1;
			_experience._next = previousNext;
			_healthPoints._levelHP -= _healthPoints._increment;
			_healthPoints._currentHP = getMaxHP();
			previousNext = getPreviousNext();
		}
		else // Level min
		{
			if (_experience._current < 0)
				_experience._current = 0;
			break;
		}
	}
}

void StatisticsComponent::addHp(long amount)
{
	_healthPoints._currentHP = std::min(_healthPoints._currentHP + amount, getMaxHP());
}

void StatisticsComponent::removeHp(long amount)
{
	_healthPoints._currentHP = std::max(_healthPoints._currentHP - amount, static_cast<long>(0));
}

long long StatisticsComponent::getPreviousNext()
{
	// Get the amount of exp required for the previous level
	long long startingNext = 150; // Initial amount of xp
	long long previousNext = 150; 
	while ((startingNext *= _experience._increment) && startingNext < _experience._next)
		previousNext = startingNext;
	return previousNext;
}
