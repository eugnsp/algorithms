// Diving for gold
// ---------------
//
// Goal: select which treasures to pick to maximize the quantity of gold recovered
//
// UVa ID: 990
// This file is covered by the LICENSE file in the root of this project.

#include "base.hpp"
#include "dp_zero_one_knapsack.hpp"
#include <cstddef>
#include <vector>
#include <iostream>
#include <cassert>

class Diving_for_gold : public Program2
{
private:
	virtual bool read_input() override
	{
		// <maximum time> <speed>
		// <number of treasures>
		// <depth_1> <amount_1>
		// ...
		// <depth_n> <amount_n>

		std::size_t n;
		std::cin >> max_time_ >> speed_ >> n;

		if (!std::cin)
			return false;

		treasures_.resize(n);
		for (auto& t : treasures_)
		{
			std::cin >> t.depth >> t.amount;
			assert(t.depth > 0 && t.amount > 0);
		}

		return true;
	}

	virtual void solve(std::size_t i_case) override
	{
		const auto weight = [this](std::size_t i) { return 3 * speed_ * treasures_[i].depth; };
		const auto value = [this](std::size_t i) { return treasures_[i].amount; };
		
		const auto ts = knapsack_max_value_and_items(treasures_.size(), max_time_, weight, value);

		if (i_case > 0)
			std::cout << '\n';

		std::cout << ts.first << '\n' << ts.second.size() << '\n';
		for (const auto i : ts.second)
			std::cout << treasures_[i].depth << ' ' << treasures_[i].amount << '\n';
	}

private:
	struct Treasure
	{
		unsigned int amount;
		unsigned int depth;
	};

	unsigned int max_time_;
	unsigned int speed_;
	std::vector<Treasure> treasures_;
};

int main()
{
	Diving_for_gold p;
	return p.run();
}