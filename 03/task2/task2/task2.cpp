#include <iostream>
#include <vector>
#include <algorithm>
#include <future>

template <typename Iterator, typename Func>
void parallel_for_each_block(Iterator begin, Iterator end, Func&& func) {
	std::for_each(begin, end, std::forward<Func>(func));
}

template <typename Iterator, typename Func>
void parallel_for_each_helper(Iterator begin, Iterator end, Func&& func, size_t num_threads) {
	size_t size = std::distance(begin, end);
	size_t chunk_size = (size + num_threads - 1) / num_threads;

	// Базовый случай рекурсии: если размер контейнера меньше или равен размеру блока, используем std::for_each.
	if (size <= chunk_size) {
		std::for_each(begin, end, std::forward<Func>(func));
		return;
	}

	// В противном случае, разделяем контейнер на две части и рекурсивно обрабатываем каждую часть.
	Iterator mid = std::next(begin, size / 2);

	// Запускаем первую половину асинхронно через лямбда-функцию.
	std::future<void> first_half = std::async(std::launch::async, [&]() {
		parallel_for_each_helper(begin, mid, std::forward<Func>(func), num_threads / 2);
		});

	// Обрабатываем вторую половину синхронно.
	parallel_for_each_helper(mid, end, std::forward<Func>(func), num_threads - num_threads / 2);

	// Ожидаем завершения асинхронной задачи (первой половины).
	first_half.wait();
}

template <typename Iterator, typename Func>
void parallel_for_each(Iterator begin, Iterator end, Func&& func, size_t num_threads = std::thread::hardware_concurrency()) {
	parallel_for_each_helper(begin, end, std::forward<Func>(func), num_threads);
}

int main() {
	std::vector<int> data = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };

	std::cout << "Исходный список: ";
	for (int num : data) {
		std::cout << num << " ";
	}
	std::cout << std::endl;

	auto multiply_by_2 = [](int& num) {
		num *= 2;
	};

	parallel_for_each(data.begin(), data.end(), multiply_by_2);

	std::cout << "Измененный список: ";
	for (int num : data) {
		std::cout << num << " ";
	}
	std::cout << std::endl;

	return 0;
}
