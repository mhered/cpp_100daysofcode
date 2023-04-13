
#include <iostream>
#include <vector>
#include <gtest/gtest.h>

// the code to test

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
    float median;
    if (arr.empty())
        throw std::invalid_argument("Cannot calculate median of empty vector");

    if (arr.size() == 1)
        return arr[0];

    arr = BubbleSort(arr, verbose);

    if (arr.size() % 2 == 0) // even number of elements
        median = (arr[arr.size() / 2] + arr[arr.size() / 2 - 1]) / 2;
    else
        median = arr[arr.size() / 2]; // odd number of elements
    if (verbose)
        std::cout << "Median : " << median << std::endl;
    return median;
}

// A parametrized test
// a struct to hold the parametrized test cases, a constructor and a streamer
struct Sample
{
    std::vector<float> input;
    float expected;

    // constructor
    Sample(std::vector<float> input, float expected) : input(input), expected(expected){};

    // we override the << operator to have a stream method for Sample
    friend std::ostream &operator<<(std::ostream &os, const Sample &obj)
    {
        os << "input: ";
        for (auto elem : obj.input)
            os << elem << ' ';
        return os
               << " expected: " << obj.expected;
    }
};

// create a fixture class derived from the struct of parametrized test cases
struct MedianTest : testing::Test, testing::WithParamInterface<Sample>
{
};

// the parametric test
TEST_P(MedianTest, ParametricTest)
{
    // get parameters
    auto sample = GetParam();
    // call the function with the input to calculate the actual result
    float output = Median(sample.input);
    // assert result matches expected
    EXPECT_EQ(sample.expected, output);
}

INSTANTIATE_TEST_CASE_P(Default, MedianTest,
                        testing::Values(
                            // Even number of integers
                            Sample({342, 98, 5456, 32, 786, 432, 890, 321}, 387),
                            Sample({32786, 7837, 83736, 83736, 10383, 738393}, 58261),
                            Sample({0, 0, 0, 0}, 0),
                            Sample({238, 432, 897, 710}, 571),
                            // Odd number of integers
                            Sample({20, 40, 20, 30, 50, 60, 70, 0, 20}, 30),
                            Sample({32, 5, 78, 32, 4, 5, 3}, 5),
                            Sample({7685, 83736, 38376, 73638, 7337}, 38376),
                            // Float median
                            Sample({1, 0, 1, 0, 0, 0, 1, 1}, 0.5),
                            // Negative values
                            Sample({-20, 40, 30, -2, 40, -13}, 14),
                            Sample({-30, -42, -60, -10, -30, -50}, -36)

                                ));

// A standalone test of an exception
TEST(EdgeCasesTest, EmptyVectorThrowsExceptionTest)
{
    // initialize empty vector
    std::vector<float> empty_vec = {};

    EXPECT_THROW({ // check that the call throws the expected exception
        try
        {
            float output = Median(empty_vec);
        }
        catch (const std::invalid_argument &e) // check that the exception has the correct message
        {
            EXPECT_STREQ(e.what(), "Cannot calculate median of empty vector"); // need STREQ to compare C strings
            throw;                                                             // rethow the exception
        }
    },
                 std::invalid_argument);
}

// invoking the tests
int main(int argc, char *argv[])
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
