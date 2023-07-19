#include <iostream>
#include <thread>
#include <atomic>

std::atomic<int> clientCounter = 0; // Atomic client counter
const int MAX_CLIENTS = 10;         // максимальное число клиентов

void clientThread()
{
	while (true)
	{
		if (clientCounter >= MAX_CLIENTS)
		{
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
		if (clientCounter <= 0)
		{
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

	clientThreadObj.join();
	operatorThreadObj.join();

	return 0;
}
