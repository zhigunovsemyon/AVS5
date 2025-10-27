#include "filler.h"
#include "task1.h"
#include "task2.h"
#include "task3.h"

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
	using arr_type = int;
	constexpr arr_type begin = 0;
	constexpr arr_type end = 10;
	constexpr bool disable_print = true;
	constexpr std::size_t arr_size = 900;

	std::vector<arr_type> nums(arr_size);

	dt();
	random_array_fill(std::span{nums}, begin, end);
	std::println("Заполено {} числами за {:4f} секунд\n", arr_size, dt());

	auto ret = task1<arr_type, disable_print>(std::span{nums});
	std::println("Сложены массивы на {} чисел за {:4f} секунд\n", ret, dt());

	ret = task2<arr_type, disable_print>(std::span{nums}, my_less);
	std::println("Рассортирован слиянием массив на {} чисел за {:4f} секунд\n", ret, dt());

	ret = task2<arr_type, disable_print>(std::span{nums}, std::greater<arr_type>{});
	std::println("Рассортирован слиянием массив в обратную сторону на {} чисел за {:4f} секунд\n", ret, dt());

	random_array_fill(std::span{nums}, begin, end);
	std::println("Заполено {} числами за {:4f} секунд\n", arr_size, dt());
	
	ret = task3<arr_type, disable_print>(std::span{nums}, my_less);
	std::println("Быстрая сортировка массива на {} чисел за {:4f} секунд\n", ret, dt());

	ret = task3<arr_type, disable_print>(std::span{nums}, std::greater{});
	std::println("Быстрая сортировка массива в обратную сторону на {} чисел за {:4f} секунд\n", ret, dt());
	
	return 0;
}
