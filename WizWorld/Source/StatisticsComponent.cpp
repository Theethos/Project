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
	m_Experience.m_Current += amount;
	while (m_Experience.m_Current >= m_Experience.m_Next)
	{
		if (m_Experience.m_Level < 50)
		{
			m_Experience.m_Level += 1;
			m_Experience.m_Next *= m_Experience._increment;
			m_HealthPoints.m_LevelHP += m_HealthPoints._increment;
			m_HealthPoints.m_CurrentHP = GetMaxHP();
			m_Mana.m_LevelMana += m_Mana._increment;
			m_Mana.m_CurrentMana = GetMaxMana();
		}
		else // Level max
		{
			m_Experience.m_Current = m_Experience.m_Next;
			break;
		}
	}
}

void StatisticsComponent::RemoveExp(long long amount)
{
	m_Experience.m_Current -= amount;
	long long previousNext = GetPreviousNext();
	while (m_Experience.m_Current < previousNext)
	{
		if (m_Experience.m_Level > 1)
		{
			m_Experience.m_Level -= 1;
			m_Experience.m_Next = previousNext;
			m_HealthPoints.m_LevelHP -= m_HealthPoints._increment;
			m_HealthPoints.m_CurrentHP = GetMaxHP();
			m_Mana.m_LevelMana -= m_Mana._increment;
			m_Mana.m_CurrentMana = GetMaxMana();
			previousNext = GetPreviousNext();
		}
		else // Level min
		{
			if (m_Experience.m_Current < 0)
				m_Experience.m_Current = 0;
			break;
		}
	}
}

void StatisticsComponent::AddHp(long amount)
{
	m_HealthPoints.m_CurrentHP = std::min(m_HealthPoints.m_CurrentHP + amount, GetMaxHP());
}

void StatisticsComponent::RemoveHp(long amount)
{
	m_HealthPoints.m_CurrentHP = std::max(m_HealthPoints.m_CurrentHP - amount, static_cast<long>(0));
}

void StatisticsComponent::AddMana(long amount)
{
	m_Mana.m_CurrentMana = std::min(m_Mana.m_CurrentMana + amount, GetMaxMana());
}

void StatisticsComponent::RemoveMana(long amount)
{
	m_Mana.m_CurrentMana = std::max(m_Mana.m_CurrentMana - amount, static_cast<long>(0));
}

long long StatisticsComponent::GetPreviousNext()
{
	// Get the amount of exp required for the previous level
	long long startingNext = 150; // Initial amount of xp
	long long previousNext = 150; 
	while ((startingNext *= m_Experience._increment) && startingNext < m_Experience.m_Next)
		previousNext = startingNext;
	return previousNext;
}
