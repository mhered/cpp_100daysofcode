#include <iostream>
#include <vector>

int secondLargest(std::vector<int> arr)
{
    int max = INT32_MIN;
    int second = INT32_MIN;
    for (int x : arr)
    {
        if (x >= max)
        {
            second = max;
            max = x;
        }

        else if (x >= second)
        {
            second = x;
        }
    }
    return second;
}

int main()
{
    std::cout << secondLargest({10, 40, 30, 20, 50}) << std::endl;   // 40
    std::cout << secondLargest({25, 143, 89, 13, 105}) << std::endl; // 105
    std::cout << secondLargest({54, 23, 11, 17, 10}) << std::endl;   // 23
    std::cout << secondLargest({10, 10}) << std::endl;               // 10

    return 0;
}