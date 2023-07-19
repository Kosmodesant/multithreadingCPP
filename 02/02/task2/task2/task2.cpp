#include <iostream>
#include <thread>
#include <chrono>
#include <mutex>
#include <vector>

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
        std::cout << "Thread " << thread_num << " (" << std::this_thread::get_id() << "): [";
        for (int j = 0; j < progress; ++j)
            std::cout << "#";
        for (int j = progress; j < 50; ++j)
            std::cout << "-";
        std::cout << "] " << i + 1 << "/" << duration << "\r";
        std::cout.flush();
    }
    auto end_time = std::chrono::high_resolution_clock::now();
    double total_time = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time).count() / 1000.0;

    // Выводим суммарное время работы потока
    std::lock_guard<std::mutex> lock(mtx);
    std::cout << "\nThread " << thread_num << " finished in " << total_time << " seconds.\n";
}

int main() {
    // Количество потоков и длительность расчёта
    int num_threads = 16;
    int duration = 60;

    std::vector<std::thread> threads;
    for (int i = 1; i <= num_threads; ++i) {
        threads.emplace_back(calculate, i, duration);
    }

    // Запускаем все потоки
    for (auto& thread : threads) {
        thread.join();
    }

    std::cout << "All threads have finished.\n";

    return 0;
}
