#include <iostream>
#include <vector>
#include <Windows.h>
#include <thread>
#include <mutex>
#include <random>

using namespace std;
once_flag o_flag;
mutex mtx;
const int y_position = 15;

void once_print() {
	cout << "#\tID\t Progress Bar  \tTime\n";
}

void cursor_position(int x, int y) {
	COORD p = { x, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), p);
}
void completion(int i, int num_threads) {

	for (int j = 1; j <= num_threads; j++) {
		mtx.lock();
		cursor_position((y_position + j), i);
		this_thread::sleep_for(100ms);
		cout << "#";
		mtx.unlock();
		this_thread::sleep_for(300ms);
	}
	cout << "\t";
}

void print(int i, int num_threads) {
	auto start = chrono::high_resolution_clock::now();
	call_once(o_flag, once_print);
	mtx.lock();
	cursor_position(0, i);
	cout << i << "\t" << this_thread::get_id();
	mtx.unlock();
	completion(i, num_threads);
	auto end = chrono::high_resolution_clock::now();
	chrono::duration<double> time = end - start;
	mtx.lock();
	cursor_position((y_position + num_threads + 5), i);
	cout << time.count() << "s";
	mtx.unlock();
}

int main() {
	int num_threads = 16;
	int duration = 10;
	vector<thread> threads;
	for (int i = 1; i <= num_threads; i++) {
		threads.push_back(thread(print, i, duration));
	}
	for (auto& t : threads) {
		t.join();
	}
	cursor_position(0, (num_threads + 1));
	std::cout << "\n";
	std::cout << "All threads have finished.\n";
	return 0;
}