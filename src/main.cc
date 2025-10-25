#include "filler.h"
#include "printer.h"
#include "task1.h"

#include <vector>

template <class T>
concept SortConcept = std::copy_constructible<T> && std::three_way_comparable<T>;

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
