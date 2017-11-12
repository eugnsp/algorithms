/*********************************************************************
Cutting sticks
--------------
UVa ID: 10003

Goal:	find the minimum cost for cutting a stick at the given points.

This file is covered by the LICENSE file in the root of this project.
**********************************************************************/

#include "base.hpp"
#include "matrix.hpp"
#include <cstddef>
#include <vector>
#include <algorithm>
#include <cassert>

class Cutting_sticks : public CP2
{
private:
	static constexpr std::size_t max_size = static_cast<std::size_t>(-1);

private:
	virtual bool read_input(std::istream& in) override
	{
		// <stick length>
		// <number of cuts = n>
		// <cut position 1> ... <cut position n>

		in >> length_;
		if (length_ == 0)
			return false;

		assert(length_ < 1000);

		in >> n_cuts_;
		assert(n_cuts_ < 50);

		cut_poss_.resize(n_cuts_);
		for (auto& c : cut_poss_)
		{
			in >> c;
			assert(c < length_);
		}

		assert(std::is_sorted(cut_poss_.cbegin(), cut_poss_.cend()));
		return true;
	}

	virtual void solve(std::ostream& out, std::size_t) override
	{
		/*********************************************************************
		m(i, j) is the minimum cost of cutting the stick such that
			all cuts in the range (i, j) has been made.

		The recurrence relation is:
			m(i, j) = min {i < k < j} [cost_ij + m(i, k) + m(k, j)],			
			where (cost_ij) is the cost of cutting the stick segment ([i, j]).

		The base case:
			m(i, i + 1) = 0 for all (i).
		**********************************************************************/

		cut_poss_.insert(cut_poss_.begin(), 0);
		cut_poss_.push_back(length_);
		n_cuts_ = cut_poss_.size();

		m_.resize_and_fill(n_cuts_, n_cuts_, max_size);
		for (std::size_t i = 1; i < n_cuts_; ++i)
			m_(i - 1, i) = 0;

		for (std::size_t d = 2; d < n_cuts_; ++d)
			for (std::size_t i = 0; i < n_cuts_ - d; ++i)
			{
				const auto j = i + d;
				for (std::size_t k = i + 1; k < j; ++k)
				{
					const auto cost = cut_poss_[j] - cut_poss_[i];
					m_(i, j) = std::min(m_(i, j), m_(i, k) + m_(k, j) + cost);
				}
			}

		out << "The minimum cutting is " << m_(0, n_cuts_ - 1) << ".\n";
	}

private:
	std::size_t length_;
	std::size_t n_cuts_;
	std::vector<std::size_t> cut_poss_;
	Matrix<std::size_t> m_;
};

int main()
{
	Cutting_sticks p;
	return p.run();
}
