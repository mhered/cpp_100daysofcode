#include <iostream>
#include <thread>
#include <chrono>
#include <mutex>

// Mutex to protect the console output (std::cout)
std::mutex mtConsole;

void worker_functionC(int thread_number, int iterations, long delay)
{
    int loop = 0;
    // Loop some 'iterations' number of times
    while (loop < iterations)
    {
        // Sleep for some time
        std::this_thread::sleep_for(std::chrono::milliseconds(delay));
        // Get the lock on the console
        mtConsole.lock();
        std::cout << "Thread " << thread_number << " Reporting: " << loop << " with delay " << delay << std::endl;
        // Remove the lock on the console
        mtConsole.unlock();
        loop++;
    }
}

int main()
{
    char result;
    // Launch two new threads. They will start executing immediately
    std::thread worker_thread1(worker_functionC, 1, 10, 2000);
    std::thread worker_thread2(worker_functionC, 2, 10, 2000);

    // Pause the main thread
    std::cout << "Press a key to finish" << std::endl;
    std::cin >> result;

    // Join up the two worker threads to the main thread
    worker_thread1.join();
    worker_thread2.join();
    // Return success
    return 1;
}