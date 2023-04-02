#include <iostream>
#include <vector>

void showMatrix(std::vector<std::vector<int>> matrix)
{

    for (auto row : matrix)
    {
        for (auto elem : row)
        {
            std::cout << elem << " " << std::flush;
        }
        std::cout << std::endl;
    }
}

std::vector<std::vector<int>> transposeMatrix(std::vector<std::vector<int>> arr)
{
    uint rows = arr.size();
    uint cols = arr[0].size();

    std::vector<std::vector<int>> transpose(cols, std::vector<int>(rows));
    for (uint i = 0; i < rows; i++)
    {
        for (uint j = 0; j < cols; j++)
        {
            transpose[j][i] = arr[i][j];
        }
    }
    return transpose;
}

int main()
{
    std::vector<std::vector<int>> matrix{
        {1, 2, 3},
        {4, 5, 6},
        {7, 8, 9},
        {10, 11, 12}};

    showMatrix(matrix);
    std::vector<std::vector<int>> transposed = transposeMatrix(matrix);
    std::cout << "Transposed:" << std::endl;
    showMatrix(transposed);

    return 0;
}