#pragma once
#include "printer.h"

#include <algorithm>
#include <print>
#include <span>
#include <vector>
#include <cassert>
#include <omp.h>

template <typename T, typename sorter> int64_t qsort_key_pick(std::span<T> arr, sorter sort_type) 
{
	return (int64_t)arr.size() / 2;
	(void)sort_type;
}

template <typename T, typename sorter>
auto qsort_partition(std::span<T> arr, sorter sort_type)
{
	int64_t iend = (int64_t)arr.size() - 1;
		
	int64_t ikey = qsort_key_pick(arr, sort_type);
	std::swap(arr[(size_t)ikey], arr[(size_t)iend]);
	ikey = iend--;

	int64_t j = -1;
	int64_t i;
	for (i = 0; i < ikey; ++i) {

		//при проходе по большей половине всегда будет это
		if (sort_type(arr[(size_t)ikey], arr[(size_t)i])) {
			continue;
		} 
		//else:
		std::swap(arr[(size_t)(++j)], arr[(size_t)i]);
	}
	// j сам перестанет расти, когда в оставшеёся половине все элементы будут больше
	std::swap(arr[(size_t)ikey], arr[(size_t)j + 1]);
		
	return arr.begin() + (j + 1);
}

template <typename T, typename sorter>
void quicksort(std::span<T> arr, sorter sort_type)
{
	if (arr.size() < 2) {
		return;
	}
	auto split_it = qsort_partition(arr, sort_type);

#pragma omp parallel sections
	{

#pragma omp section
	quicksort(std::span{split_it + 1, arr.end()}, sort_type);
		
#pragma omp section
	quicksort(std::span{arr.begin(), split_it}, sort_type);

	}
}

template <typename T, bool no_print = false, typename sorter> auto task3(std::span<T> arr, sorter sort_type)
{
	omp_set_max_active_levels((int)ceil(log2(omp_get_max_threads())));
	if (no_print) {
		quicksort(arr, sort_type);
		return arr.size();
	}

	std::println("До сортировки:");
	print_array(arr);

	quicksort(arr, sort_type);

	std::println("После сортировки:");
	print_array(arr);

	return arr.size();
}
