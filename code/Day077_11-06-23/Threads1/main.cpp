#include <iostream>
#include <thread>

// The Hello, World! of threads

void display(int xN) {
    std::cout << "Hello Thread: " << xN << "\n";
}

int main() {
    std::thread t1(display, 1);
    t1.join();
}

