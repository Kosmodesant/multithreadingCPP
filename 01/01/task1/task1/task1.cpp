#include <iostream>
#include <thread>
#include <mutex>

std::mutex mtx;  // Мьютекс для синхронизации доступа к счетчику клиентов
int clientCounter = 0;  // Счетчик клиентов
const int MAX_CLIENTS = 10;  // Максимальное количество клиентов

void clientThread()
{
    while (true)
    {
        // Увеличиваем счетчик клиентов
        std::lock_guard<std::mutex> lock(mtx);
        if (clientCounter >= MAX_CLIENTS)
        {
            // Достигнуто максимальное количество клиентов
            break;
        }
        ++clientCounter;
        std::cout << "Новый клиент! Всего клиентов: " << clientCounter << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
}

void operatorThread()
{
    while (true)
    {
        // Уменьшаем счетчик клиентов
        std::lock_guard<std::mutex> lock(mtx);
        if (clientCounter <= 0)
        {
            // Больше нет клиентов
            break;
        }
        --clientCounter;
        std::cout << "Обслужен клиент! Осталось клиентов: " << clientCounter << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(2));
    }
}

int main()
{
    setlocale(LC_ALL, "Russian");
    std::thread clientThreadObj(clientThread);
    std::thread operatorThreadObj(operatorThread);

    // Ждем завершения потоков
    clientThreadObj.join();
    operatorThreadObj.join();

    return 0;
}
