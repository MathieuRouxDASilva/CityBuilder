#include "gameplay/economy_manager.h"

EconomyManager::EconomyManager()
{
	//statring money
	constexpr int starting_economy = 5000;
	economy_ = starting_economy;
}

void EconomyManager::ReduceEconomyBy(const size_t number)
{
	economy_ -= number;
}

void EconomyManager::IncreaseEconomyBy(const size_t number)
{
	economy_ += number;
}

size_t EconomyManager::economy() const
{
	return economy_;
}
