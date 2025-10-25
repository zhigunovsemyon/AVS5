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

int main()
{
	using arr_type = int;
	constexpr arr_type begin = 10;
	constexpr arr_type end = -10;
	constexpr bool disable_print = false;
	constexpr std::size_t arr_size = 27;

	std::vector<arr_type> nums(arr_size);

	double start_time = omp_get_wtime();
	random_array_fill(std::span{nums}, begin, end);
	std::println("Заполено {} числами за {:4f} секунд", arr_size, omp_get_wtime() - start_time);

	start_time = omp_get_wtime();
	std::println("Сложены массивы на {} чисел за {:4f} секунд", task1<arr_type, disable_print>(std::span{nums}),
		     omp_get_wtime() - start_time);

	return 0;
}
