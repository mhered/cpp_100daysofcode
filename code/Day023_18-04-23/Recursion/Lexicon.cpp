#include "Lexicon.h"
#include <fstream>
#include <string>
#include <algorithm>
#include <iostream>

Lexicon::Lexicon()
{
}

Lexicon::~Lexicon()
{
}

Lexicon::Lexicon(std::string filename)
{

    // ifstream is used for reading files
    // We'll read from a file called Sample.txt
    std::ifstream inf{filename};

    // If we couldn't open the input file stream for reading
    if (!inf)
    {
        // Print an error and exit
        std::cerr << "Uh oh, " << filename << " could not be opened for reading!\n";
    }

    else
        // While there's still stuff left to read
        while (inf)
        {
            // read stuff from the file into a string and print it
            std::string word;
            std::getline(inf, word);
            std::transform(word.begin(), word.end(), word.begin(),
                           [](unsigned char c)
                           { return std::tolower(c); });
            corpus.push_back(word);
        }
}

bool Lexicon::contains(std::string word)
{
    std::transform(word.begin(), word.end(), word.begin(),
                   [](unsigned char c)
                   { return std::tolower(c); });
    for (auto elem : corpus)
        if (word == elem)
        {
            std::cout << word << " found" << std::endl;
            return true;
        }
    // std::cout << word << " not found" << std::endl;

    return false;
}