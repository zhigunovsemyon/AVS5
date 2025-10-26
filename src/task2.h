#pragma once
#include "printer.h"

#include <algorithm>
#include <print>
#include <span>
#include <vector>
#include <omp.h>

template <typename T, typename sorter> void mergesort(std::span<T> arr, std::span<T> buf, sorter sort_type)
{
	assert(arr.size());
	assert(arr.size() == buf.size());
	if (arr.size() == 1) {
		return;
	}

	auto mid_point_arr = arr.begin() + arr.size() / 2;
	std::span<T> lhs_arr{arr.begin(), mid_point_arr}, rhs_arr{mid_point_arr, arr.end()};
	auto mid_point_buf = buf.begin() + buf.size() / 2;
	std::span<T> lhs_buf{buf.begin(), mid_point_buf}, rhs_buf{mid_point_buf, buf.end()};

#pragma omp parallel sections
	{
#pragma omp section
		mergesort(lhs_arr, lhs_buf, sort_type);

#pragma omp section
		mergesort(rhs_arr, rhs_buf, sort_type);
	}

	std::copy(lhs_arr.begin(), lhs_arr.end(), lhs_buf.begin());
	std::copy(rhs_arr.begin(), rhs_arr.end(), rhs_buf.begin());

	auto i = lhs_buf.begin(); // итератор левой копии
	auto j = rhs_buf.begin(); // итератор правой копии

	for (auto & it : arr) {
		if (i == lhs_buf.end()) {
			it = *(j++);
			continue;
		}
		if (j == rhs_buf.end()) {
			it = *(i++);
			continue;
		}

		it = sort_type(*i, *j) ? *(i++) : *(j++);
	}
}

template <typename T, bool no_print = false, typename sorter> auto task2(std::span<T> big_arr, sorter sort_type)
{
	auto mid_point = big_arr.begin() + big_arr.size() / 2;
	std::span<T> arr{big_arr.begin(), mid_point};
	std::span<T> buf{mid_point, mid_point + arr.size()};
	assert((buf.size() + arr.size()) <= big_arr.size());

	omp_set_max_active_levels((int)ceil(log2(omp_get_max_threads()))); 
	if (no_print) {
		mergesort(arr, buf, sort_type);
		return arr.size();
	}

	std::println("До сортировки:");
	print_array(arr);

	mergesort(arr, buf, sort_type);

	std::println("После сортировки:");
	print_array(arr);

	return arr.size();
}