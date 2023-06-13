#include <iostream>
#include <thread>
#include <chrono>
#include <mutex>
#include <vector>

// Mutex to protect our price array
std::mutex mtPriceArray;

// Create an array to hold our prices
std::vector<double> dblPriceArray;

void data_writer()
{
    // Write our market data into dblPriceArray
    while (1)
    {
        // random delay
        // Sleep for some random time up to 5 seconds
        std::this_thread::sleep_for(std::chrono::milliseconds(rand() % 5000));
        // Lock the price array
        mtPriceArray.lock();
        // Create a price and load it into the array
        // In a real application we would be pulling this price from our market data source
        dblPriceArray.push_back(20.0 * (1 + (rand() % 100) / 1000.0));
        // Unlock the price array
        mtPriceArray.unlock();
    }
}

void data_reader(int delay)
{
    unsigned int loop = 0;
    double dblSum = 0;
    double dblAverage = 0;
    while (1)
    {
        // Get the lock on the price array
        mtPriceArray.lock();
        if (dblPriceArray.size() > 0)
        {
            // Calculate the average
            dblSum = 0.0;
            for (loop = 0; loop < dblPriceArray.size(); loop++)
            {
                dblSum += dblPriceArray[loop];
            }
            dblAverage = dblSum / dblPriceArray.size();
            std::cout << "Latest Price: " << dblPriceArray[dblPriceArray.size() - 1];
            std::cout << " Average: " << dblAverage << std::endl;
        }
        // Unlock the price array vector
        mtPriceArray.unlock();
        // Sleep for some time
        std::this_thread::sleep_for(std::chrono::milliseconds(delay));
    } // end while
}

int main()
{
    char result;
    // Launch two new threads. They will start executing immediately
    std::thread writer_thread(data_writer);
    std::thread reader_thread(data_reader, 1000);

    // Pause the main thread
    std::cout << "Press a key to finish" << std::endl;
    std::cin >> result;

    // Join up the two worker threads to the main thread
    writer_thread.join();
    reader_thread.join();
    // Return success
    return 1;
}
