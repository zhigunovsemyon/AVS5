#pragma once
#include "printer.h"

#include <span>
#include <algorithm>
#include <print>

template <typename T, bool no_print = false, typename sorter> auto task2(std::span<T> arr, sorter sort_type)
{
	if (no_print) {
		std::ranges::sort(arr, sort_type);
		return arr.size();
	}

	std::println("До сортировки:");
	print_array(arr);

	std::ranges::sort(arr, sort_type);

	std::println("После сортировки:");
	print_array(arr);

	return arr.size();
}