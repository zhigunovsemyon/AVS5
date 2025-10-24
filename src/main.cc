#include "printer.h"
#include <compare>
#include <cstddef>
#include <omp.h>
#include <random>
#include <span>
#include <utility>
#include <vector>

template <class T>
concept SortConcept = std::copy_constructible<T> && std::three_way_comparable<T>;

std::mt19937_64 g_rand{std::random_device{}()};

template <std::floating_point T> void random_array_fill(std::span<T> array, T min, T max)
{
	auto const arr_size = array.size();
	auto local_rand = g_rand;

	if (min > max) {
		std::swap(min, max);
	}
	auto dist = std::uniform_real_distribution<T>(min, max);

#pragma omp parallel for shared(array, arr_size, dist) private(local_rand)
	for (std::size_t i = 0; i < arr_size; ++i) {
		array[i] = dist(local_rand);
	}
}

template <std::integral T> void random_array_fill(std::span<T> array, T min, T max)
{
	auto const arr_size = array.size();
	auto local_rand = g_rand;

	if (min > max) {
		std::swap(min, max);
	}
	auto dist = std::uniform_int_distribution<T>(min, max);

#pragma omp parallel for shared(array, arr_size, dist) private(local_rand)
	for (std::size_t i = 0; i < arr_size; ++i) {
		array[i] = dist(local_rand);
	}
}

int main()
{
	constexpr std::size_t arr_size = 100;
	std::vector<double> nums(arr_size);
	random_array_fill(std::span{nums}, 11200.4, 120.0);
	print_array(std::span{nums});
	return 0;
}
