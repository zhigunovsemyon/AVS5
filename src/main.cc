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
	constexpr std::size_t arr_size = 50;
	std::vector<double> nums(arr_size);

	random_array_fill(std::span{nums}, 1120.0, 1.200);
	print_array(std::span{nums});
	return 0;
}
