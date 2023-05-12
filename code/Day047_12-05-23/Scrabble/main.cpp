#include <iostream>
#include <vector>
#include <map>

std::map<char, int> SCRABBLE_SCORES = {
    {'A', 1},
    {'B', 3},
    {'C', 3},
    {'D', 2},
    {'E', 1},
    {'F', 4},
    {'G', 2},
    {'H', 4},
    {'I', 1},
    {'J', 8},
    {'K', 5},
    {'L', 2},
    {'M', 3},
    {'N', 1},
    {'O', 1},
    {'P', 3},
    {'Q', 10},
    {'R', 1},
    {'S', 1},
    {'T', 1},
    {'U', 1},
    {'V', 4},
    {'W', 4},
    {'X', 8},
    {'Y', 4},
    {'Z', 10}};

int scrabble_score(std::string word, bool verbose = false)
{
    int score = 0;
    for (auto ch : word)
    {
        score += SCRABBLE_SCORES[toupper(ch)];
    }
    if (verbose)
        std::cout << "\"" << word << "\": " << score << ", " << std::flush;
    return score;
}

std::vector<std::string> bestWords(std::vector<std::string> arr, bool verbose = false)
{
    std::vector<std::string> result;
    int max_score = 0;

    if (verbose)
        std::cout << "\nWord scores: ";

    for (auto word : arr)
    {
        int score = scrabble_score(word, verbose);
        if (score > max_score)
        {
            // found word with score higher than max_score:
            // replace previous list of words with this word
            // and update max_score
            result.clear();
            result.push_back(word);
            max_score = score;
        }
        else if (score == max_score)
        {
            // found word with score same as max_score:
            // append to list of words
            result.push_back(word);
        }
    }
    // display
    if (verbose)
    {
        std::cout << "\nTop score (" << max_score << "): ";
        for (auto word : result)
        {
            std::cout << "\"" << word << "\", " << std::flush;
        }
        std::cout << std::endl;
    }
    return result;
}

// auxiliary function to print a vector
std::string print_vector(std::vector<std::string> vector, std::string separator = "\",\"")
{
    std::string str = "{\"";
    for (int i = 0; i < vector.size(); i++)
    {
        str += vector[i];
        if (i < vector.size() - 1)
            str += separator;
    }
    return str + "\"}";
}

int main()
{
    bool verbose = false; // if true it prints more info on score per word, max score etc

    std::vector<std::vector<std::string>> samples =
        {
            {"got", "test", "oh", "sat", "rents"},               // std::vector<std::string>{"oh","rents"}
            {"digest", "divest", "verge", "honey", "money"},     // std::vector<std::string>{"honey"}
            {"wig", "jury", "interim", "size", "hunter"},        // std::vector<std::string>{"jury"}
            {"berry", "whiz", "laughed", "ghetto", "psychic"},   // std::vector<std::string>{"whiz", "psychic"}
            {"library", "index", "memory", "ghosts", "quit"},    // std::vector<std::string>{"library","index","memory","quit"}
            {"singing", "swine", "llamas", "crunchy", "creamy"}, // std::vector<std::string>{"crunchy"}
        };

    std::vector<std::string> vec;

    for (auto sample : samples)
    {
        vec = bestWords(sample, verbose);
        std::cout << "bestWords(" << print_vector(sample) << ") -> " << print_vector(vec) << std::endl;
    }

    return 0;
}
