#pragma once
#include <omp.h>
#include <random>
#include <span>

template <std::floating_point T> void random_array_fill(std::span<T> array, std::mt19937_64 local_rand, T min, T max)
{
	auto const arr_size = array.size();

	if (min > max) {
		std::swap(min, max);
	}

#pragma omp parallel for shared(array, arr_size) private(local_rand)
	for (std::size_t i = 0; i < arr_size; ++i) {
		array[i] = std::uniform_real_distribution<T>{min, max}(local_rand);
	}
}

template <std::integral T> void random_array_fill(std::span<T> array, std::mt19937_64 local_rand, T min, T max)
{
	auto const arr_size = array.size();

	if (min > max) {
		std::swap(min, max);
	}

#pragma omp parallel for shared(array, arr_size, dist) private(local_rand)
	for (std::size_t i = 0; i < arr_size; ++i) {
		array[i] = std::uniform_int_distribution<T>{min, max}(local_rand);
	}
}
