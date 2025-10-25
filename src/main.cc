#include "filler.h"
#include "printer.h"

#include <algorithm>
#include <cassert>
#include <cstddef>
#include <omp.h>
#include <span>
#include <vector>

template <class T>
concept SortConcept = std::copy_constructible<T> && std::three_way_comparable<T>;

template <class T> void sum_arrays(std::span<T> const vec1, std::span<T> const vec2, std::span<T> vec3)
{
	assert(vec1.size() == vec2.size() && vec2.size() == vec3.size());
	long mid_point = vec1.size() / 2;

#pragma omp parallel sections num_threads(2)
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

template <class T> void task1(std::span<T> big_array)
{
	ssize_t subarray_size = big_array.size() / 3;
	auto p0 = big_array.begin();
	auto p1 = p0 + subarray_size;
	auto p2 = p1 + subarray_size;
	auto p3 = p2 + subarray_size;

	std::span<T> vec1{p0, p1}, vec2{p1, p2}, vec3{p2, p3};
	sum_arrays(vec1, vec2, vec3);

	std::println("Первый массив:");
	print_array(std::span{vec1});
	std::println("Второй массив:");
	print_array(std::span{vec2});
	std::println("Третий массив:");
	print_array(std::span{vec3});
}

int main()
{
	constexpr std::size_t arr_size = 100;
	std::vector<double> nums(arr_size);

	random_array_fill(std::span{nums}, -1.0, 1.0);
	task1(std::span{nums});
	return 0;
}
