#include <iostream>
#include <vector>

void PrintVector(std::vector<float> vec)
{
    for (auto elem : vec)
        std::cout << elem << ' ';
}

std::vector<float> BubbleSort(std::vector<float> arr, bool verbose = false)
{
    // degraded case, no need to sort
    if (arr.size() < 2)
        return arr;

    // bubble sorting
    bool swap = false;
    int pass = 0;
    do
    {
        swap = false;
        pass++;
        for (int i = 0; i < arr.size() - 1; i++)
        {
            if (arr[i] > arr[i + 1]) // swap if smaller than
            {
                float tmp = arr[i + 1];
                arr[i + 1] = arr[i];
                arr[i] = tmp;
                swap = true;
            }
        }
        if (verbose)
        {
            std::cout << "Pass " << pass << ": " << std::flush;
            PrintVector(arr);
            std::cout << std::endl;
        }
    } while (swap);
    return arr;
}

std::vector<float> RandVector(int size = 1, float min = 0, float max = 1)
{
    std::vector<float> vec;
    for (int i = 0; i < size; i++)
        vec.push_back(rand() * (max - min) / RAND_MAX + min);
    return vec;
}

float Median(std::vector<float> arr, bool verbose = false)
{

    if (arr.empty())
        throw std::invalid_argument("Cannot calculate median of empty vector");

    if (arr.size() == 1)
        return arr[0];

    arr = BubbleSort(arr, verbose);
    float median;
    if (arr.size() % 2 == 0) // even number of elements
        median = (arr[arr.size() / 2] + arr[arr.size() / 2 - 1]) / 2;
    else
        median = arr[arr.size() / 2]; // odd number of elements
    std::cout << "Median : " << median << std::endl;
    return median;
}

int main()
{

    float median;
    try
    {
        median = Median({}, true);
    }
    catch (const std::invalid_argument &e)
    {
        std::cerr << "Exception: " << e.what() << std::endl;
    }

    median = Median({2}, true);
    median = Median({2, 1, 4, 5}, true);
    median = Median({2, 5, 6, 2, 6, 3, 4}, true);              // ➞ 4
    median = Median({21.4323, 432.54, 432.3, 542.4567}, true); // ➞ 432.4
    median = Median({-23, -43, -29, -53, -67}, true);          // ➞ -43
    median = Median(RandVector(17, -13.7, 4.8), true);

    return 0;
}


