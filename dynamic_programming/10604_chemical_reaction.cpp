/*********************************************************************
Chemical reaction
-----------------
UVa ID: 10604

Goal:	find the least total heat generated upon mixing chemicals.

This file is covered by the LICENSE file in the root of this project.
**********************************************************************/

#include "base.hpp"
#include "matrix.hpp"
#include <cstddef>
#include <vector>
#include <algorithm>
#include <limits>
#include <iostream>
#include <cassert>

class Chemical_reaction : public CP1
{
private:
	struct Mix
	{
		std::size_t type;
		int heat;
	};

private:
	virtual void read_input() override
	{
		// <number of types of chemicals = n>
		// mixing table:
		// <type_11> <heat_11>
		// ...
		// <type_nn> <heat_nn>
		// <number of tubes = k>
		// <chemical_1> ... <chemical_k>
		// <'/' or '.'>

		std::cin >> n_types_;
		assert(1 <= n_types_ && n_types_ <= 6);

		mixing_table_.resize(n_types_, n_types_);
		for (std::size_t i = 0; i < n_types_; ++i)
			for (std::size_t j = 0; j < n_types_; ++j)
			{
				auto& c = mixing_table_(i, j);
				std::cin >> c.type >> c.heat;
				--c.type;	// To zero-based indexing
			}

		std::cin >> n_tubes_;
		assert(2 <= n_tubes_ && n_tubes_ <= 10);

		chemicals_.resize(n_tubes_);
		for (auto& c : chemicals_)
		{
			std::cin >> c;
			--c;	// To zero-based indexing
		}

		char c_ignore;
		std::cin >> c_ignore;
		assert(c_ignore == '/' || c_ignore == '.');
	}

	virtual void solve(std::size_t) override
	{
		/*********************************************************************
		mh(tch) is the minimum heat generated by mixing all chemicals in a set
			of tubes, such that (count = tch[i]) tubes contain chemical
			of the (i)-th type, i < (number of types of chemicals).

		The recurrence relation is:
			mh(tch) = min {i <= j} [mh(tch_ij) + mix(i, j).heat],
				where (tch_ij) is (tch) with i-th and j-th chemicals removed
				and (mix(i, j).type) chemical added.

		Base case:
			mh(tch) = 0, if (tch) contains only one chemical (nothing to mix).
		**********************************************************************/

		std::size_t mh_size = 1;
		for (std::size_t i = 0; i < n_types_; ++i)
			mh_size *= (n_tubes_ + 1);

		mh_.assign(mh_size, std::numeric_limits<int>::max());

		std::vector<std::size_t> tch(n_types_, 0);
		for (auto c : chemicals_)
			++tch[c];

		std::cout << min_heat(tch) << '\n';
	}

	int min_heat(const std::vector<std::size_t>& tch)
	{
		assert(tch.size() == n_types_);

		const auto ind = index(tch);
		assert(ind < mh_.size());

		auto& m = mh_[ind];
		if (m != std::numeric_limits<int>::max())
			return m;

		for (std::size_t i = 0; i < n_types_; ++i)
			for (std::size_t j = 0; j < n_types_; ++j)
				if ((i != j && tch[i] >= 1 && tch[j] >= 1) || (i == j && tch[i] >= 2))
				{
					const auto& mixed = mixing_table_(i, j);
					auto tch_with_ij_mixed = tch;
					--tch_with_ij_mixed[i];
					--tch_with_ij_mixed[j];
					++tch_with_ij_mixed[mixed.type];

					m = std::min(m, min_heat(tch_with_ij_mixed) + mixed.heat);
				}

		// Nothing to mix
		if (m == std::numeric_limits<int>::max())
			m = 0;

		return m;
	}

	std::size_t index(const std::vector<std::size_t>& tch) const
	{
		std::size_t index = 0;
		for (auto c : tch)
			index = (n_tubes_ + 1) * index + c;
		
		return index;
	}

private:
	std::size_t n_types_;
	std::size_t n_tubes_;
	std::vector<int> mh_;
	Matrix<Mix> mixing_table_;
	std::vector<std::size_t> chemicals_;
};

int main()
{
	Chemical_reaction p;
	return p.run();
}
