#include <iostream>
#include <fstream>
#include <vector>


std::vector<int> findChar(std::string str, char chr)
{
    // helper function to find all occurences of a char in a string
    std::vector<int> positions = {};
    for (int i = 0; i < str.size(); i++)
        if (str[i] == chr)
            positions.push_back(i);

    return positions;
}

bool readMorseTable(std::string filename)
{

    // ifstream is used for reading files
    std::ifstream inf{filename};

    // If we couldn't open the input file stream for reading
    if (!inf)
    {
        // Print an error and exit
        std::cerr << "Uh oh, " << filename << " could not be opened for reading!\n";
        return false;
    }

    std::vector<int> column_delimiters = {};
    std::vector<int> prosign_delimiters = {};
    std::string line = "";
    std::string symbol = "";
    std::string morse = "";

    // Skip header
    std::getline(inf, line);
    std::getline(inf, line);
    std::getline(inf, line);

    // Scan table
    while (inf)
    {
        column_delimiters = findChar(line, '|');
        if (column_delimiters.size() == 3)
        {
            uint pos1 = column_delimiters[0] + 2;
            uint len1 = column_delimiters[1] - column_delimiters[0] - 3;
            symbol = line.substr(pos1, len1);
            // prosign
            prosign_delimiters = findChar(symbol, '<');
            if (!prosign_delimiters.empty())
            {
                int p1 = prosign_delimiters[0];
                prosign_delimiters = findChar(symbol, '>');
                int p2 = prosign_delimiters[0];
                symbol = symbol.substr(p1, p2 - p1 + 1);
            }

            uint pos2 = column_delimiters[1] + 2;
            uint len2 = column_delimiters[2] - column_delimiters[1] - 3;
            morse = line.substr(pos2, len2);

            std::cout << "{\"" << symbol << "\" , \"" << morse << "\"}," << std::endl;
        }
        std::getline(inf, line);
    }

    return true;
}

int main()
{
    std::string filename = "morse_table.md";

    if (!readMorseTable(filename))
    {
        std::cerr << "Read operation failed." << std::endl;
    }
}

