#include <iostream>
#include <vector>

bool canPartition(std::vector<int> arr)
{
    int prod = 1;
    int count_zeroes = 0;

    // compute product
    for (int x : arr)
    {
        if (x == 0)
        {
            count_zeroes++;
            // check edge case more than one zero
            if (count_zeroes > 1)
                return true;
        }
        prod *= x;
    }

    // check condition
    for (int x : arr)
    {
        if (x != 0 && prod / x == x) // avoid division by zero, edge case was checked above
        {
            return true;
        }
    }
    return false;
}

int main()
{
    std::cout << canPartition({2, 8, 4, 1}) << std::endl;            // true
    std::cout << canPartition({-1, -10, 1, -2, 20}) << std::endl;    // false
    std::cout << canPartition({-1, -20, 5, -1, -2, 2}) << std::endl; // true
    std::cout << canPartition({0, 1, 1, -1}) << std::endl;           // false
    std::cout << canPartition({0, 0, 1, -1}) << std::endl;           // true
    return 0;
}