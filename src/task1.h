#pragma once
#include <algorithm>
#include <cassert>
#include <omp.h>
#include <cstddef>
#include <span>

template <class T> void sum_arrays(std::span<T> const vec1, std::span<T> const vec2, std::span<T> vec3)
{
	assert(vec1.size() == vec2.size() && vec2.size() == vec3.size());
	auto mid_point = static_cast<std::int64_t>(vec1.size()) / 2;

#pragma omp parallel sections // потоков не будет больше двух
	{

#pragma omp section
		std::transform(vec1.begin() + mid_point, //
			       vec1.end(),		 //
			       vec2.begin() + mid_point, //
			       vec3.begin() + mid_point, //
			       std::plus{});

#pragma omp section
		std::transform(vec1.begin(), vec1.begin() + mid_point, vec2.begin(), vec3.begin(), std::plus{});
	}
}

template <class T, bool no_print = false> auto task1(std::span<T> big_array)
{
	auto subarray_size = static_cast<std::int64_t>(big_array.size()) / 3;
	auto p0 = big_array.begin();
	auto p1 = p0 + subarray_size;
	auto p2 = p1 + subarray_size;
	auto p3 = p2 + subarray_size;

	std::span<T> vec1{p0, p1}, vec2{p1, p2}, vec3{p2, p3};
	sum_arrays(vec1, vec2, vec3);

	if (no_print) {
		return vec2.size();
	}

	std::println("Первый массив:");
	print_array(std::span{vec1});
	std::println("Второй массив:");
	print_array(std::span{vec2});
	std::println("Третий массив:");
	print_array(std::span{vec3});
	return vec2.size();
}