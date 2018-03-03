/*********************************************************************
The Hamming distance problem
----------------------------
UVa ID: 729

This file is covered by the LICENSE file in the root of this project.
**********************************************************************/

#include "base.hpp"
#include "util.hpp"
#include <algorithm>
#include <cassert>
#include <string>
#include <vector>

using Pos = unsigned int;

class Hamming_distance_strings
{
private:
	using Strings = std::vector<std::string>;

public:
	Hamming_distance_strings(Pos string_length, Pos hamming_dist)
		: length_(string_length), n_zeros_(string_length - hamming_dist)
	{
		assert(hamming_dist <= string_length);
	}

	Strings enumerate_strings() const
	{
		Strings strings;
		std::string init_string(length_, '1');

		get_next(strings, init_string, 0);
		return strings;
	}

private:
	void get_next(Strings& strings, std::string& string, Pos pos) const
	{
		if (has_max_zeros(string))
			strings.push_back(string);
		else
			for (Pos i = pos; i < length_; ++i)
			{
				string[i] = '0';
				get_next(strings, string, i + 1);
				string[i] = '1';
			}
	}

	bool has_max_zeros(const std::string& string) const
	{
		return std::count(string.begin(), string.end(), '0') == n_zeros_;
	}

private:
	const Pos length_;
	const Pos n_zeros_;
};

class CP : public CP1
{
private:
	virtual void read_input(std::istream& in) override
	{
		in >> string_length_ >> hamming_dist_;
		assert(hamming_dist_ <= string_length_ && string_length_ <= 16);
	}

	virtual void solve(std::ostream& out, std::size_t i_case) const override
	{
		if (i_case > 0)
			out << '\n';

		const Hamming_distance_strings hds(string_length_, hamming_dist_);
		for (auto& str : hds.enumerate_strings())
			out << str << '\n';
	}

private:
	Pos string_length_;
	Pos hamming_dist_;
};

int main()
{
	CP p;
	return p.run();
}
