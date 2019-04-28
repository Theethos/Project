#include "Precompiled_Header.h"
#include "../Include/Macros.h"
#include "../Include/StatisticsComponent.h"

// Constructor
StatisticsComponent::StatisticsComponent()
{}
// Destructor
StatisticsComponent::~StatisticsComponent()
{}

void StatisticsComponent::AddExp(long long amount)
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
			_mana._levelMana += _mana._increment;
			_mana._currentMana = getMaxMana();
		}
		else // Level max
		{
			_experience._current = _experience._next;
			break;
		}
	}
}

void StatisticsComponent::RemoveExp(long long amount)
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
			_mana._levelMana -= _mana._increment;
			_mana._currentMana = getMaxMana();
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

void StatisticsComponent::AddHp(long amount)
{
	_healthPoints._currentHP = std::min(_healthPoints._currentHP + amount, getMaxHP());
}

void StatisticsComponent::RemoveHp(long amount)
{
	_healthPoints._currentHP = std::max(_healthPoints._currentHP - amount, static_cast<long>(0));
}

void StatisticsComponent::AddMana(long amount)
{
	_mana._currentMana = std::min(_mana._currentMana + amount, getMaxMana());
}

void StatisticsComponent::RemoveMana(long amount)
{
	_mana._currentMana = std::max(_mana._currentMana - amount, static_cast<long>(0));
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
