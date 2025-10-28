#include "filler.h"
#include "task1.h"
#include "task2.h"
#include "task3.h"

#include <omp.h>
#include <vector>

template <class T>
concept SortConcept = std::copy_constructible<T> && std::three_way_comparable<T>;

static double dt() 
{ 
	static double prev_ = omp_get_wtime();
	auto cur = omp_get_wtime();
	auto ret = cur - prev_;
	prev_ = cur;
	return ret;
}

int main()
{
	auto my_less = [](auto a, auto b) { return a < b; };	
	using arr_type = double;
	constexpr arr_type begin = 0;
	constexpr arr_type end = 10;
	constexpr bool disable_print = true;
	constexpr std::size_t arr_size = 1'000'000'000;

	std::vector<arr_type> nums(arr_size);

	omp_set_num_threads(8);
	omp_set_max_active_levels((int)ceil(log2(omp_get_max_threads())));

	dt();
	std::println("Заполнение массива на {} чисел", arr_size);
	random_array_fill(std::span{nums}, begin, end);
	std::println("Заполено за {:f} сек\n", dt());

	std::println("Cложение массивов C = A + B");
	auto ret = task1<arr_type, disable_print>(std::span{nums});
	std::println("Сложены массивы на {} чисел за {:f} сек\n", ret, dt());

	std::println("Проход по несортированному массиву методом слияния");
	ret = task2<arr_type, disable_print>(std::span{nums}, my_less);
	std::println("Массив на {} чисел рассортирован за {:f} сек\n", ret, dt());

	std::println("Проход по отсортированному массиву методом слияния");
	ret = task2<arr_type, disable_print>(std::span{nums}, my_less);
	std::println("Массив на {} чисел рассортирован за {:f} сек\n", ret, dt());

	std::println("Проход по отсортированному наоборот массиву методом слияния");
	ret = task2<arr_type, disable_print>(std::span{nums}, std::greater<arr_type>{});
	std::println("Массив на {} чисел рассортирован за {:f} сек\n", ret, dt());

	random_array_fill(std::span{nums}, begin, end);
	std::println("Заполено {} числами за {:f} сек\n", arr_size, dt());
	
	std::println("Проход по несортированному массиву методом быстрой сортировки");
	ret = task3<arr_type, disable_print>(std::span{nums}, my_less);
	std::println("Массив на {} чисел рассортирован за {:f} сек\n", ret, dt());

	std::println("Проход по сортированному наоборот массиву методом быстрой сортировки");
	ret = task3<arr_type, disable_print>(std::span{nums}, std::greater{});
	std::println("Массив на {} чисел рассортирован за {:f} сек\n", ret, dt());
	
	std::println("Проход по сортированному массиву методом быстрой сортировки");
	ret = task3<arr_type, disable_print>(std::span{nums}, std::greater{});
	std::println("Массив на {} чисел рассортирован за {:f} сек\n", ret, dt());
	
	return 0;
}
