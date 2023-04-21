#include <iostream>
#include <vector>
#include <string>

#include <gtest/gtest.h>

// code to test

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

int sum_vector(std::vector<int> vector)
{
    int sum = 0;
    for (auto x : vector)
        sum += x;
    return sum;
}

std::vector<std::vector<int>> RecSumUp(int target,
                                       std::vector<int> numbers,
                                       std::vector<int> partial,
                                       std::vector<std::vector<int>> solutions)
{
    int sum = sum_vector(partial);

    if (sum == target)
    {
        // base case: found a combination that adds to target
        // add it to the list of solutions
        solutions.push_back(partial);
    }

    // if not yet there, keep looking
    if (sum < target)
    {
        for (int i = 0; i < numbers.size(); i++)
        {
            // for each number
            // add the number to a copy of partial
            std::vector<int> partial_rec = partial;
            partial_rec.push_back(numbers[i]);

            // remove all previous numbers from the list of remaining (keep i to allow repetition)
            std::vector<int> remaining(numbers.begin() + i, numbers.end());

            // recurse
            solutions = RecSumUp(target, remaining, partial_rec, solutions);
        }
    }
    // we reach here if sum > target (solution not valid)

    // or being sum < target what??

    // if (sum < target)
    //    std::cout << "what?" << std::endl;

    // return without adding new solutions to the list
    return solutions;
}

std::vector<std::vector<int>> CombinationsThatSum(int target, std::vector<int> numbers, bool verbose = false)
{
    std::vector<std::vector<int>> solutions = RecSumUp(target, numbers, {}, {});
    if (verbose)
    {
        for (int i = 0; i < solutions.size(); i++)
        {
            std::cout << target << " =" << print_vector(solutions[i], " + ") << std::endl;
        }
        std::cout << "Found " << solutions.size() << " combinations of {"
                  << print_vector(numbers, ", ") << "} that sum " << target << std::endl;
    }
    return solutions;
}

// A parametrized test
// a struct to hold the parametrized test cases, a constructor and a streamer
struct Sample
{
    std::vector<int> input;
    int target;
    int expected;

    // constructor
    Sample(int target, std::vector<int> input, int expected) : target(target), input(input), expected(expected){};

    // we override the << operator to have a stream method for Sample
    friend std::ostream &operator<<(std::ostream &os, const Sample &obj)
    {
        os << "target: " << obj.target << " input: {";
        for (auto elem : obj.input)
            os << elem << ' ';
        return os
               << "} expected: " << obj.expected;
    }
};

/*
// create a fixture class derived from the struct of parametrized test cases
struct CombisTest : testing::Test, testing::WithParamInterface<Sample>
{
};

// the parametric test
TEST_P(CombisTest, ParametricTest)
{
    // get parameters
    auto sample = GetParam();
    // call the function with the input to calculate the actual result
    std::vector<std::vector<int>> output;
    output = CombinationsThatSum(sample.target, sample.input, true);
    // assert result matches expected

    EXPECT_EQ(sample.expected, (int)output.size());
}

INSTANTIATE_TEST_CASE_P(Default, CombisTest,
                        testing::Values(
                            Sample(8, {1, 2, 3, 4, 5, 6, 7, 8}, 22),
                            Sample(15, {3, 9, 8, 4, 5, 7, 10}, 10),
                            Sample(4, {1, 2}, 3),
                            Sample(10, {5, 2, 3}, 4),
                            Sample(11, {5, 7}, 0),
                            Sample(11, {1, 2, 5}, 11),
                            Sample(37, {1, 2, 5, 10}, 160)));

// invoking the tests
int main(int argc, char *argv[])
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

*/

int main()
{

    std::vector<Sample> samples = {
        Sample(5, {1, 2, 3, 4, 5}, 7),
        Sample(8, {1, 2, 3, 4, 5, 6, 7, 8}, 22),
        Sample(15, {3, 9, 8, 4, 5, 7, 10}, 10),
        Sample(4, {1, 2}, 3),
        Sample(10, {5, 2, 3}, 4),
        Sample(11, {5, 7}, 0),
        Sample(11, {1, 2, 5}, 11),
        Sample(37, {1, 2, 5, 10}, 160),
        Sample(219, {2, 5, 10, 20, 50}, 1859)};

    for (auto sample : samples)
    {
        std::vector<std::vector<int>> solutions = CombinationsThatSum(sample.target, sample.input, true);
        std::cout << "Expected: " << sample.expected << std::endl;
    }
    return 0;
}
