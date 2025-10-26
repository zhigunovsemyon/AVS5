#pragma once
#include "printer.h"

#include <algorithm>
#include <print>
#include <span>
#include <vector>
#include <omp.h>

template <typename T, typename sorter>
void quicksort(std::span<T> arr, sorter sort_type)
{

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