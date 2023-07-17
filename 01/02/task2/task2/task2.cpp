#include <iostream>
#include <vector>
#include <thread>
#include <numeric>
#include <chrono>

// Функция для расчета суммы двух векторов
template <typename T>
T parallelSum(const std::vector<T>& vec1, const std::vector<T>& vec2)
{
    std::vector<T> result(vec1.size());

    std::size_t numThreads = std::thread::hardware_concurrency();
    std::vector<std::thread> threads(numThreads);

    std::size_t blockSize = vec1.size() / numThreads;
    std::size_t lastBlockSize = vec1.size() % numThreads;

    std::size_t startIdx = 0;

    for (std::size_t i = 0; i < numThreads; ++i)
    {
        std::size_t blockSizeWithRemainder = blockSize + (i < lastBlockSize ? 1 : 0);
        std::size_t endIdx = startIdx + blockSizeWithRemainder;

        threads[i] = std::thread([&, startIdx, endIdx]() {
            for (std::size_t j = startIdx; j < endIdx; ++j)
            {
                result[j] = vec1[j] + vec2[j];
            }
            });

        startIdx = endIdx;
    }

    for (auto& thread : threads)
    {
        thread.join();
    }

    return std::accumulate(result.begin(), result.end(), static_cast<T>(0));
}

int main()
{
    std::size_t numElements[] = { 1000, 10000, 100000, 1000000 };
    std::size_t numThreads[] = { 2, 4, 8, 16 };

    std::cout << "Available hardware concurrency: " << std::thread::hardware_concurrency() << std::endl;
    std::cout << "-----------------------------------------" << std::endl;
    std::cout << "|  Num Elements  |  Num Threads  |  Time  |" << std::endl;
    std::cout << "-----------------------------------------" << std::endl;

    for (std::size_t elements : numElements)
    {
        for (std::size_t threads : numThreads)
        {
            std::vector<int> vec1(elements, 1);
            std::vector<int> vec2(elements, 2);

            auto startTime = std::chrono::steady_clock::now();

            int sum = parallelSum(vec1, vec2);

            auto endTime = std::chrono::steady_clock::now();
            auto elapsedTime = std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime);

            std::cout << "| " << std::setw(14) << elements << " | " << std::setw(12) << threads << " | "
                << std::setw(5) << elapsedTime.count() << " ms |" << std::endl;
        }
    }

    std::cout << "-----------------------------------------" << std::endl;

    return 0;
}
