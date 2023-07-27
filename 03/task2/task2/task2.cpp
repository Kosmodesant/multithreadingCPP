#include <iostream>
#include <vector>
#include <algorithm>
#include <future>

template <typename Iterator, typename Func>
void parallel_for_each_block(Iterator begin, Iterator end, Func&& func) {
    std::for_each(begin, end, std::forward<Func>(func));
}

template <typename Iterator, typename Func>
void parallel_for_each(Iterator begin, Iterator end, Func&& func, size_t num_threads = std::thread::hardware_concurrency()) {
    size_t size = std::distance(begin, end);
    size_t chunk_size = (size + num_threads - 1) / num_threads;

    std::vector<std::future<void>> futures;
    futures.reserve(num_threads);

    for (Iterator it = begin; it < end; std::advance(it, chunk_size)) {
        Iterator block_end = std::min(std::next(it, chunk_size), end);

        // Используем std::packaged_task для обертки функции
        std::packaged_task<void()> task([it, block_end, &func]() {
            parallel_for_each_block(it, block_end, func);
            });

        futures.push_back(task.get_future());
        std::thread(std::move(task)).detach();
    }

    // Ожидаем завершения всех задач
    for (auto& future : futures) {
        future.wait();
    }
}

int main() {
    std::vector<int> data = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };

    std::cout << "Original List: ";
    for (int num : data) {
        std::cout << num << " ";
    }
    std::cout << std::endl;

    auto multiply_by_2 = [](int& num) {
        num *= 2;
    };

    parallel_for_each(data.begin(), data.end(), multiply_by_2);

    std::cout << "Modified List: ";
    for (int num : data) {
        std::cout << num << " ";
    }
    std::cout << std::endl;

    return 0;
}
