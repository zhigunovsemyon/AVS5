#pragma once
#include <concepts>
#include <span>
#include <print>

template <std::floating_point T> void print_array(std::span<T> const array)
{
	for (auto const & n : array) {
		std::print("{:.5f}; ", n);
	}
	std::println();
}

template <std::integral T> void print_array(std::span<T> const array)
{
	for (auto const & n : array) {
		std::print("{} ", n);
	}
	std::println();
}

