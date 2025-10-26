#include "filler.h"
#include "task1.h"
#include "task2.h"

#include <vector>

template <class T>
concept SortConcept = std::copy_constructible<T> && std::three_way_comparable<T>;

int main()
{
	using arr_type = int;
	constexpr arr_type begin = 10;
	constexpr arr_type end = -10;
	constexpr bool disable_print = true;
	constexpr std::size_t arr_size = 1'207'000'000;

	std::vector<arr_type> nums(arr_size);

	double new_time, start_time = omp_get_wtime();
	random_array_fill(std::span{nums}, begin, end);
	new_time = omp_get_wtime();
	std::println("Заполено {} числами за {:4f} секунд", arr_size, new_time - start_time);
	start_time = new_time;

	auto ret = task1<arr_type, disable_print>(std::span{nums});
	new_time = omp_get_wtime();
	std::println("Сложены массивы на {} чисел за {:4f} секунд", ret, new_time - start_time);
	start_time = new_time;

	ret = task2<arr_type, disable_print>(std::span{nums}, std::less{});
	new_time = omp_get_wtime();
	std::println("Рассортирован слиянием массив на {} чисел за {:4f} секунд", ret, new_time - start_time);

	return 0;
}
