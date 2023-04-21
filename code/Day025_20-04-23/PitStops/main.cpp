#include <fstream>
#include <vector>

#include <sstream>

#include <iostream>
#include <string>
#include <regex>
#include <limits.h>

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

// auxiliary function to add elements of a vector
int sum_vector(std::vector<int> vector)
{
    int sum = 0;
    for (auto x : vector)
        sum += x;
    return sum;
}

// recursive function to find combinations of numbers that add to a target
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

// wrapper for the recursive function to find combinations of numbers that add to a target
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

// auxiliary function: split a string by a separator
std::vector<std::string> split(const std::string str,
                               const std::string regex_str)
{
    std::regex regexz(regex_str);
    return {std::sregex_token_iterator(str.begin(), str.end(), regexz, -1),
            std::sregex_token_iterator()};
}

// struct to repreent a Car
struct Car
{
    int tankCapacity;
    std::vector<int> lapTimes;

    // we override the << operator to have a stream method for Sample
    friend std::ostream &operator<<(std::ostream &os, const Car &obj)
    {
        os << "tankCapacity: " << obj.tankCapacity << " full laps" << std::endl;

        os << "lapTimes: " << std::endl;
        for (int i = 0; i < obj.lapTimes.size(); i++)
        {
            os << "   " << obj.lapTimes[i] << "s with fuel for " << i + 1 << " laps" << std::endl;
        }
        return os;
    }
};

// struct to represent a Race
struct Race
{
    long pitstopTime;
    int numLaps;
    long bestTime(Car car);
    std::vector<int> bestStrategy(int nLaps, Car car);
    long evaluate(std::vector<int> setStints, Car car);

    // we override the << operator to have a stream method for Sample
    friend std::ostream &operator<<(std::ostream &os, const Race &obj)
    {
        return os << " " << obj.numLaps << " laps, " << obj.pitstopTime << "s pit stop ";
    }
};

// Race method to determine the best race strategy
std::vector<int> Race::bestStrategy(int nLaps, Car car)
{
    std::vector<int> stints;
    for (int i = 0; i < nLaps; i++)
    {
        stints.push_back(i + 1);
    }

    std::vector<std::vector<int>> all_combinations = CombinationsThatSum(nLaps, stints, false);
    std::vector<int> bestCombination = {};
    long bestRaceTime = INT_MAX;
    for (int i = 0; i < all_combinations.size(); i++)
    {
        int raceTime = evaluate(all_combinations[i], car);
        if (raceTime < bestRaceTime)
        {
            bestCombination = all_combinations[i];
            bestRaceTime = raceTime;
        }
    }
    return bestCombination;
};

long Race::evaluate(std::vector<int> setStints, Car car)
{
    long result = 0;
    for (int i = 0; i < setStints.size(); i++)
    {
        for (int j = 0; j < setStints[i]; j++)
            result += car.lapTimes[j];
        result += pitstopTime;
    }
    return result;
};

long Race::bestTime(Car car)
{

    int nFullTanks = numLaps / car.tankCapacity;
    int lastStint = numLaps % car.tankCapacity;

    long bestTime = 0;
    std::vector<int> bestStrategyFullTank = bestStrategy(car.tankCapacity, car);
    bestTime += evaluate(bestStrategyFullTank, car) * nFullTanks;
    std::vector<int> bestStrategyPartiallyFullTank = bestStrategy(lastStint, car);
    bestTime += evaluate(bestStrategyPartiallyFullTank, car) - pitstopTime;

    return bestTime;
};

bool readInputFromFile(std::string filename,
                       Car &car,
                       std::vector<Race> &races,
                       bool verbose = false)
{

    // ifstream is used for reading files
    std::ifstream inf{filename};

    // If we couldn't open the input file stream for reading
    if (!inf)
    {
        // Print an error and exit
        std::cerr << filename << " could not be opened for reading\n";
        return false;
    }

    // variables
    // int tankCapacity;
    // std::vector<int> lapTimes;

    int numRaces;
    // std::vector<long int> pitstopTime;
    // std::vector<int> numLaps;
    std::string line;

    // get tankCapacity and numRaces
    std::getline(inf, line);
    std::vector<std::string> tokens = split(line, " ");
    car.tankCapacity = std::stoi(tokens[0]);
    numRaces = std::stoi(tokens[1]);

    // get lapTimes as a function of fuel load
    std::getline(inf, line);
    tokens = split(line, " ");

    for (int i = 0; i < tokens.size(); i++)
    {
        car.lapTimes.push_back(std::stoi(tokens[i]));
    }

    if (verbose)
    {
        std::cout << car << std::endl;
    }

    // get races
    if (verbose)
    {
        std::cout << "numRaces: " << numRaces << std::endl;
    }
    for (int i = 0; i < numRaces; i++)
    {
        std::getline(inf, line);
        tokens = split(line, " ");
        Race race;
        race.numLaps = std::stoi(tokens[0]);
        race.pitstopTime = std::stol(tokens[1]);
        races.push_back(race);
        if (verbose)
        {
            std::cout << "Race #" << i + 1 << ": " << races[i] << std::endl;
        }
    }

    return true;

    // When inf goes out of scope, the ifstream
    // destructor will close the file
}

int main()
{

    Car car;
    std::vector<Race> racesList;

    std::string filename = "input.txt";

    if (!readInputFromFile(filename, car, racesList, false))
    {
        std::cerr << "Read operation failed." << std::endl;
    }

    std::cout << car << std::endl;
    std::cout << "numRaces: " << racesList.size() << std::endl;
    for (int i = 0; i < racesList.size(); i++)
    {
        std::cout << "Race #" << i + 1 << ": " << racesList[i] << std::endl;
    }
    std::cout << std::string(50, '#') << std::endl;
    for (int i = 0; i < racesList.size(); i++)
    {
        long t = racesList[i].bestTime(car);
        std::cout << "Race #" << i + 1 << ": best time is " << t << "s" << std::endl;
    }

    return 0;
}