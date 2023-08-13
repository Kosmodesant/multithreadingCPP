#include <iostream>
#include <vector>
#include <queue>
#include <thread>
#include <functional>
#include <mutex>
#include <condition_variable>

class safe_queue {
private:
    std::queue<std::function<void()>> tasks;
    std::mutex mtx;
    std::condition_variable cv;

public:
    void push(std::function<void()> task) {
        std::unique_lock<std::mutex> lock(mtx);
        tasks.push(task);
        cv.notify_one();
    }

    std::function<void()> pop() {
        std::unique_lock<std::mutex> lock(mtx);
        cv.wait(lock, [this] { return !tasks.empty(); });
        auto task = tasks.front();
        tasks.pop();
        return task;
    }
};

class thread_pool {
private:
    std::vector<std::thread> threads;
    safe_queue task_queue;
    std::atomic<bool> stop;

public:
    thread_pool(size_t num_threads = std::thread::hardware_concurrency())
        : stop(false) {
        for (size_t i = 0; i < num_threads; ++i) {
            threads.emplace_back([this] {
                while (!stop) {
                    auto task = task_queue.pop();
                    task();
                }
                });
        }
    }

    ~thread_pool() {
        stop = true;
        for (auto& thread : threads) {
            thread.join();
        }
    }

    template <typename Func>
    void submit(Func func) {
        task_queue.push(func);
    }
};

int main() {
    thread_pool pool;

    // Тестовые функции
    auto test_function1 = [] { std::cout << "Function 1 executed" << std::endl; };
    auto test_function2 = [] { std::cout << "Function 2 executed" << std::endl; };

    // Помещаем задачи в пул потоков
    for (int i = 0; i < 5; ++i) {
        pool.submit(test_function1);
        pool.submit(test_function2);
    }

    std::this_thread::sleep_for(std::chrono::seconds(5));

    return 0;
}
