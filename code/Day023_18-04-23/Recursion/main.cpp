#include <iostream>
#include <string>
#include "Lexicon.h"

void RecPermute(std::string sofar, std::string rest)
{
    if (rest == "")
    {
        // base case: we scanned all
        // so we found a permutation, show it
        std::cout << sofar << std::endl;
    }
    else
    {
        for (int i = 0; i < rest.length(); i++)
        {
            std::string next = sofar + rest[i];
            std::string remaining = rest.substr(0, i) + rest.substr(i + 1); // goes to end of rest!
            RecPermute(next, remaining);
        }
    }
}
// wrapper function to hide the recursive function
void ListPermutations(std::string s)
{
    RecPermute("", s);
}

// enumerate all subsets. Order does not matter
void RecSubsets(std::string sofar, std::string rest)
{
    if (rest == "")
    {
        // base case: we scanned all
        // so we found a combination, show it
        std::cout << sofar << std::endl;
    }
    else
    {
        // add to subset, remove from rest, recurse
        RecSubsets(sofar + rest[0], rest.substr(1));
        // don't add to subset, remove from rest, recurse
        RecSubsets(sofar, rest.substr(1));
    }
}
// wrapper function to hide the recursive function
void ListSubsets(std::string s)
{
    RecSubsets("", s);
}

// Recursive Backtrackers are not exhaustive
// we return some info of the progress
// if success we stop exploring

/* Backtracking pseudocode
bool Solve (configuration conf)
{
    if (no more choices) // base case
    return (conf is goal state)

    for (all available choices)
    {
        try one choice c;
        // solve from here, if works out, you're done
        if (Solve(conf with choice c made))
            return true;
        unmake choice c;
    }

    return false; // tried all choices, no solution found
}
*/

bool RecIsAnagram(std::string sofar, std::string rest, Lexicon &lex)
{
    if (rest == "")
    {
        // base case: anagram found
        return lex.contains(sofar);
    }
    else
    {
        for (int i = 0; i < rest.length(); i++)
        {
            std::string next = sofar + rest[i];
            std::string remaining = rest.substr(0, i) + rest.substr(i + 1); // goes to end of rest!
            if (RecIsAnagram(next, remaining, lex))
                return true;
        }
        return false;
    }
}

// wrapper function to hide the recursive function
bool IsAnagram(std::string s, Lexicon &lex)
{
    return RecIsAnagram("", s, lex);
}

// 8 Queens Pseudocode
/*
bool Solve(Grid<bool> &board, int col)
{
    if (col >= board.numCols()) // base case
        return true;
    for (int rowToTry = 0; rowToTry < board.numRows(); rowToTry++)
    {
        // for all choices available
        if (IsSafe(board, rowToTry, col))
        {
            // make the choice
            PlaceQueen(board, rowToTry, col);

            // try to solve from here, if works out, you're done
            if (Solve(board, col + 1))
                return true;
            // if not, unmake the choice and keep looking
            RemoveQueen(board, rowToTry, col);
        }
    }
    // tried all choices, no solution found
    return false;
}
*/

int main()
{
    ListPermutations("abcd");
    std::cout << std::endl;
    ListSubsets("abcd");

    Lexicon lex("wordlist.10000.txt");
    if (!lex.contains("dormitory"))
        ;
    std::vector<std::string> words = {
        "abcd",
        "wierd",     // wired
        "warred",    // reward
        "lopes",     // slope
        "deigns",    // design
        "fortes",    // forest
        "obverse",   // observe
        "storescum", // customers
    };
    for (auto word : words)
    {
        std::cout << word << ": " << std::flush;
        if (!IsAnagram(word, lex))
            std::cout << "no anagram found" << std::endl;
    }
    return 0;
}