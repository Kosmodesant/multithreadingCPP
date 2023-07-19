#include <iostream>
#include <mutex>

class Data {
public:
    Data(int value) : data(value) {}

    void setData(int value) {
        data = value;
    }

    int getData() const {
        return data;
    }

    std::mutex& getMutex() {
        return mtx;
    }

private:
    int data;
    std::mutex mtx;
};

void swap_with_lock(Data& data1, Data& data2) {
    std::lock(data1.getMutex(), data2.getMutex());
    std::lock_guard<std::mutex> lock1(data1.getMutex(), std::adopt_lock);
    std::lock_guard<std::mutex> lock2(data2.getMutex(), std::adopt_lock);

    int temp = data1.getData();
    data1.setData(data2.getData());
    data2.setData(temp);
}

void swap_with_scoped_lock(Data& data1, Data& data2) {
    std::scoped_lock lock(data1.getMutex(), data2.getMutex());

    int temp = data1.getData();
    data1.setData(data2.getData());
    data2.setData(temp);
}

void swap_with_unique_lock(Data& data1, Data& data2) {
    std::unique_lock<std::mutex> lock1(data1.getMutex(), std::defer_lock);
    std::unique_lock<std::mutex> lock2(data2.getMutex(), std::defer_lock);
    std::lock(lock1, lock2);

    int temp = data1.getData();
    data1.setData(data2.getData());
    data2.setData(temp);
}

int main()
{
    Data data1(42);
    Data data2(73);

    std::cout << "Before swap - data1: " << data1.getData() << ", data2: " << data2.getData() << std::endl;

    swap_with_lock(data1, data2); // or swap_with_scoped_lock or swap_with_unique_lock

    std::cout << "After swap - data1: " << data1.getData() << ", data2: " << data2.getData() << std::endl;

    return 0;
}
