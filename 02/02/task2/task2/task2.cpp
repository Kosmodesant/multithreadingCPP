#include <iostream>
#include <thread>
#include <chrono>
#include <mutex>
#include <vector>
#include <iomanip> // For setw and setprecision

std::mutex mtx;

// Функция для эмуляции "расчёта" в потоке
void calculate(int thread_num, int duration) {
	auto start_time = std::chrono::high_resolution_clock::now();


	for (int i = 0; i < duration; ++i) {
		// Эмулируем некоторую вычислительную работу
		std::this_thread::sleep_for(std::chrono::milliseconds(100));

		// Выводим прогресс-бар (с использованием блокировки мьютекса для корректного вывода)
		std::lock_guard<std::mutex> lock(mtx);
		int progress = static_cast<int>((i + 1) / static_cast<double>(duration) * 50);

		std::cout <<"  "<< std::left << std::setw(10) << std::left << std::setw(5) << thread_num
			<< std::left << std::setw(10) << std::this_thread::get_id();
		for (int j = 0; j < progress; ++j)
			std::cout << (char)178;
		for (int j = progress; j < 50; ++j)
			std::cout << (char)177;
		std::cout << i + 1 << "/" << duration << "\r";
		std::cout.flush();
	}
	auto end_time = std::chrono::high_resolution_clock::now();
	double total_time = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time).count() / 1000.0;

	// Выводим суммарное время работы потока
	std::lock_guard<std::mutex> lock(mtx);
	std::cout << "  "<< std::left << std::setw(10) << std::left << std::setw(5) << thread_num
		<< std::left << std::setw(10) << std::this_thread::get_id()
		<< std::left << std::setw(10) << std::fixed << std::setprecision(2) << total_time << "\n";
}

int main() {
	/*   SetConsoleCP(1251);
	   SetConsoleOutputCP(1251);*/
	   // Количество потоков и длительность расчёта
	int num_threads = 16;
	int duration = 70;

	std::cout << "-------------------------------------------------------------------------" << std::endl;
	std::cout << "| # |   ID   |                    Time & Progress                       |" << std::endl;
	std::cout << "-------------------------------------------------------------------------" << std::endl;

	std::vector<std::thread> threads;
	for (int i = 1; i <= num_threads; ++i) {
		threads.emplace_back(calculate, i, duration);
	}

	// Запускаем все потоки
	for (auto& thread : threads) {
		thread.join();
	}
	std::cout << "\n";
	std::cout << "All threads have finished.\n";

	return 0;
}


