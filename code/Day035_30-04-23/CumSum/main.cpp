#include <iostream>
#include <vector>

// better implementation with single loop
std::vector<int> cumsum(std::vector<int> vect)
{
    std::vector<int> result;
    int running_sum = 0;
    for (int i = 0; i < vect.size(); i++)
    {
        running_sum += vect[i];
        result.push_back(running_sum);
    }
    return result;
}

// naive implementation with 2 for loops
std::vector<int> cumsum2(std::vector<int> vect)
{
    std::vector<int> result;
    for (int i = 0; i < vect.size(); i++)
    {
        int partial = 0;
        for (int j = 0; j <= i; j++)
        {
            partial += vect[j];
        }
        result.push_back(partial);
    }
    return result;
}

// auxiliary function to print a vector
std::string print_vector(std::vector<int> vector, std::string separator = " ")
{
    std::string str = " ";
    for (int i = 0; i < vector.size(); i++)
    {
        str += std::to_string(vector[i]);
        if (i < vector.size() - 1)
            str += separator;
    }
    return str + " ";
}

int main()
{
    std::vector<int> vect = {1, 0, 1, 2, 1, 3};

    std::cout << print_vector(vect) << std::endl;
    std::cout << print_vector(cumsum(vect)) << std::endl;
    std::cout << print_vector(cumsum2(vect)) << std::endl;
    return 0;
}