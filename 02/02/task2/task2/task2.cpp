#include <iostream>
#include <thread>
#include <random>
#include <mutex>
#include <vector>
#include <Windows.h>

using namespace std;
once_flag o_flag;
mutex mt;
const int y_position = 15;


void once_print() {
	cout << "Thread\tID\t Progress Bar  \tTime\n";
}

void cursor_position(int x, int y) {
	COORD p = { x, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), p);
}
void completion(int i, int lenght_thread) {

	for (int j = 1; j <= lenght_thread; j++) {
		mt.lock();
		cursor_position((y_position + j), i);
		this_thread::sleep_for(100ms);
		cout << "#";
		mt.unlock();
		this_thread::sleep_for(300ms);
	}
	cout << "\t";
}

void print(int i, int lenght_thread) {
	auto start = chrono::high_resolution_clock::now();
	call_once(o_flag, once_print);
	mt.lock();
	cursor_position(0, i);
	cout << i << "\t" << this_thread::get_id();
	mt.unlock();
	completion(i, lenght_thread);
	auto end = chrono::high_resolution_clock::now();
	chrono::duration<double> time = end - start;
	mt.lock();
	cursor_position((y_position + lenght_thread + 5), i);
	cout << time.count() << "s";
	mt.unlock();
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
	return 0;
}