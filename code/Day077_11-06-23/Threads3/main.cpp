#include <iostream>
#include <thread>
#include <vector>
#include <chrono>

void display(int n, const std::string &str)
{
    std::string msg = std::to_string(n) + " : " + str;
    // simulate slow process
    std::this_thread::sleep_for(std::chrono::milliseconds(msg.size()));
    std::cout << msg << std::endl;
}

int main()
{
    std::vector<std::string> s = {
        "A very long sentence may take ",
        "longer to print than a shorter one",
        "threads work in parallel",
        "can be faster than a sequence",
        "but without mutex",
        "the order is not guaranteed"};

    std::chrono::steady_clock::time_point begin, end;

    // BASELINE: without threads
    begin = std::chrono::steady_clock::now();
    for (int i = 0; i < s.size(); i++)
    {
        display(i, s[i]);
    }
    end = std::chrono::steady_clock::now();
    std::cout << std::endl
              << "Baseline (without threading) = " << std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() << "[µs]" << std::endl
              << std::endl;

    // With threading
    begin = std::chrono::steady_clock::now();
    // create vector of threads
    std::vector<std::thread> threads;

    // launch the callable in each thread
    //  with a different string as parameter

    for (int i = 0; i < s.size(); i++)
    {
        threads.push_back(std::thread(display, i, s[i]));
    }

    // join the threads to wait for the result
    for (auto &th : threads)
    {
        th.join();
    }
    end = std::chrono::steady_clock::now();
    std::cout << std::endl
              << "With threading = " << std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() << "[µs]" << std::endl
              << std::endl;

    return 0;
}