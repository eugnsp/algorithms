// Coin change
// -----------
//
// Goal: determine in how many ways given amount of money
// may be made up using a fixed set of coins and notes.
//
// UVa ID: 674
// This file is covered by the LICENSE file in the root of this project.

#include "base.hpp"
#include "dp_coin_change.hpp"
#include <array>
#include <iostream>

class Coin_change : public Program2
{
private:
	virtual bool read_input() override
	{
		// <amount>

		std::cin >> amount_;
		return !!std::cin;
	}

	virtual void solve(std::size_t) override
	{
		const std::array<unsigned int, 5> coins = {1, 5, 10, 25, 50};
		std::cout << n_ways_change<unsigned int>(coins, amount_) << '\n';
	}

private:
	unsigned int amount_;
};

int main()
{
	Coin_change p;
	return p.run();
}