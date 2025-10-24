#pragma once
#include <bit>
#include <omp.h>
#include <random>
#include <span>

template <std::floating_point T> void random_array_fill(std::span<T> array, T min, T max)
{
	auto const arr_size = array.size();

	if (min > max) {
		std::swap(min, max);
	}

	unsigned long base_seed = std::random_device{}();

#pragma omp parallel shared(array, arr_size, base_seed)
	{
		std::mt19937_64 local_rand{(unsigned long)omp_get_thread_num() + base_seed};
#pragma omp for
		for (std::size_t i = 0; i < arr_size; ++i) {
			array[i] = std::uniform_real_distribution<T>{min, max}(local_rand);
		}
	}
}

template <std::integral T> void random_array_fill(std::span<T> array, T min, T max)
{
	auto const arr_size = array.size();

	if (min > max) {
		std::swap(min, max);
	}

	unsigned long base_seed = std::random_device{}();

#pragma omp parallel shared(array, arr_size, base_seed)
	{
		std::mt19937_64 local_rand{(unsigned long)omp_get_thread_num() - base_seed};
#pragma omp for
		for (std::size_t i = 0; i < arr_size; ++i) {
			array[i] = std::uniform_int_distribution<T>{min, max}(local_rand);
		}
	}
}

template <typename T> void linear_fill(std::span<T> array, T begin = 0)
{
	auto const arr_size = array.size();

#pragma omp parallel for
	for (std::size_t i = 0; i < arr_size; ++i) {
		array[i] = begin + static_cast<T>(i);
	}
}
