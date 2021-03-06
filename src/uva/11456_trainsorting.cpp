/*********************************************************************
Trainsorting
------------
UVa ID: 114 56

This file is covered by the LICENSE file in the root of this project.
**********************************************************************/

#include "base.hpp"
#include <algorithm>
#include <cassert>
#include <cstddef>
#include <vector>

class CP : public CP1
{
private:
	virtual void read_input() override
	{
		write(n_cars_);
		assert(n_cars_ <= 2000);

		cars_seq_.resize(n_cars_);
		for (auto& c : cars_seq_)
			read(c.weight);
	}

	virtual void solve(unsigned int) override
	{
		/*********************************************************************
		seq(i).lis(lds) is the length of the longest increasing	(decreasing)
			sequence that starts at the element with the index (i).

		The recurrence relation is:
			seq(i).lis = max {j > i, seq(j).weight > seq(i).weight}
							seq(j).lis + 1,
			seq(i).lds = max {j > i, seq(j).weight < seq(i).weight}
							seq(j).lds + 1.

		The base case:
			seq(i).lis = 1	if there are no elements after (i)-th element
							with larger weight,
			seq(i).lds = 1	if there are no elements after (i)-th element
							with smaller weight.
		**********************************************************************/

		for (auto i = cars_seq_.rbegin(); i != cars_seq_.rend(); ++i)
		{
			i->lis_len = 1;
			i->lds_len = 1;

			for (auto j = cars_seq_.rbegin(); j < i; ++j)
			{
				if (j->weight > i->weight)
					i->lis_len = std::max(i->lis_len, j->lis_len + 1);

				if (j->weight < i->weight)
					i->lds_len = std::max(i->lds_len, j->lds_len + 1);
			}
		}

		std::size_t max_length = 0;
		for (const auto& c : cars_seq_)
			max_length = std::max(max_length, c.lis_len + c.lds_len - 1);

		write_ln(max_length);
	}

private:
	struct Cars
	{
		unsigned int weight;
		std::size_t lis_len;
		std::size_t lds_len;
	};

	std::size_t n_cars_;
	std::vector<Cars> cars_seq_;
};

MAIN
