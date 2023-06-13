#include <iostream>
#include <thread>
#include <chrono>

void worker_functionC(int thread_number, int iterations, long delay)
{
    int loop = 0;
    // Loop some 'iterations' number of times
    while (loop < iterations)
    {
        // Sleep for some time
        std::this_thread::sleep_for(std::chrono::milliseconds(delay));
        std::cout << "Thread " << thread_number << " Reporting: " << loop << " with delay " << delay << std::endl;
        loop++;
    }
}

int main()
{
    char result;
    // Launch two new threads. They will start executing immediately
    // worker_functionC is a generic worker that will take in two parameters:
    //   Number of iterations, and Sleep time
    std::thread worker_thread1(worker_functionC, 1, 10, 155);
    std::thread worker_thread2(worker_functionC, 2, 10, 222);

    // Pause the main thread
    std::cout << "Press a key to finish" << std::endl;
    std::cin >> result;

    // Join up the two worker threads to the main thread
    worker_thread1.join();
    worker_thread2.join();
    // Return success
    return 1;
}
