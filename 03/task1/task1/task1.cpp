#include <iostream>
#include <vector>
#include <algorithm>
#include <future>

// Функция для поиска минимального элемента в заданном диапазоне вектора
template <typename T>
std::future<T> find_min_async(const std::vector<T>& vec, size_t start, size_t end) {
	return std::async(std::launch::async, [&vec, start, end]() {
		return *std::min_element(vec.begin() + start, vec.begin() + end);
		});
}

// Функция для сортировки выбором
template <typename T>
std::vector<T> selection_sort(const std::vector<T>& input) {
	std::vector<T> sorted = input;
	size_t size = sorted.size();

	for (size_t i = 0; i < size; ++i) {
		// Асинхронно ищем минимальный элемент
		std::future<T> future_min = find_min_async(sorted, i, size);

		// Ожидаем результат поиска
		T min_element = future_min.get();

		// Находим индекс минимального элемента в оставшейся части списка
		auto min_iter = std::find(sorted.begin() + i, sorted.end(), min_element);
		size_t min_index = std::distance(sorted.begin(), min_iter);

		// Меняем местами текущий элемент с минимальным
		std::swap(sorted[i], sorted[min_index]);
	}
	return sorted;
}

int main() {
	std::vector<int> data = { 64, 34, 25, 12, 22, 11, 90 };

	// Выводим неотсортированный список
	std::cout << "Original List: ";
	for (int num : data) {
		std::cout << num << " ";
	}
	std::cout << std::endl;

	// Сортируем список
	std::vector<int> sorted_data = selection_sort(data);

	// Выводим отсортированный список
	std::cout << "Sorted List: ";
	for (int num : sorted_data) {
		std::cout << num << " ";
	}
	std::cout << std::endl;

	return 0;
}
