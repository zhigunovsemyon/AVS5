#include "filler.h"
#include "printer.h"

#include <cstddef>
#include <random>
#include <span>
#include <vector>

template <class T>
concept SortConcept = std::copy_constructible<T> && std::three_way_comparable<T>;

int main()
{
	constexpr std::size_t arr_size = 100;
	std::vector<double> nums(arr_size);

	std::mt19937_64 rand_eng{std::random_device{}()};

	random_array_fill(std::span{nums}, rand_eng, 11200.4, 120.0);
	print_array(std::span{nums});
	return 0;
}
