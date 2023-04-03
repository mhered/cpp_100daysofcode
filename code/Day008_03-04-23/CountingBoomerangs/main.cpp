#include <iostream>
#include <vector>

int countBoomerangs(std::vector<int> arr)
{
    if (arr.size() < 3)
        return 0;
    int count = 0;

    for (uint i = 0; i < arr.size() - 2; i++)
    {
        if (arr[i + 2] == arr[i] && arr[i + 1] != arr[i])
            count++;
    }
    return count;
}

void print_vector(std::vector<int> vec)
{
    for (auto elem : vec)
        std::cout << elem << ' ';
    std::cout << std::endl;
}

int main()
{

    std::cout << countBoomerangs({3, 7, 3, 2, 1, 5, 1, 2, 2, -2, 2}) << std::endl; // 3
    std::cout << countBoomerangs({1, 7, 1, 7, 1, 7, 1}) << std::endl;              // 5
    std::cout << countBoomerangs({9, 5, 9, 5, 1, 1, 1}) << std::endl;              // 2
    std::cout << countBoomerangs({5, 6, 6, 7, 6, 3, 9}) << std::endl;              // 1
    std::cout << countBoomerangs({4, 4, 4, 9, 9, 9, 9}) << std::endl;              // 0
    return 0;
}