#include <iostream>
#include <fstream>
#include <vector>

// #include <string>
#include <sstream>
// #include <ios>

bool writeTextToFile(std::string filename, std::vector<std::string> lines)
{
    // ofstream is used for writing files
    // We'll make a file called Sample.txt
    std::ofstream outf{filename};

    // If we couldn't open the output file stream for writing
    if (!outf)
    {
        // Print an error and exit
        std::cerr << "Uh  oh, " << filename << " could not be opened for writing!\n";
        return false;
    }

    // We'll write lines into this file
    for (auto line : lines)
    {
        outf << line << "\n";
    }
    return true;

    // When outf goes out of scope, the ofstream
    // destructor will close the file
}

bool appendTextToFile(std::string filename, std::vector<std::string> lines)
{
    // ofstream with option std::ios_base::app is used for appending to files
    std::ofstream outf(filename, std::ios_base::app);

    // If we couldn't open the output file stream for appending
    if (!outf)
    {
        // Print an error and exit
        std::cerr << "Uh  oh, " << filename << " could not be opened for appending!\n";
        return false;
    }

    // We'll write lines into this file
    for (auto line : lines)
    {
        outf << line << "\n";
    }
    return true;

    // When outf goes out of scope, the ofstream
    // destructor will close the file
}

bool readTextFromFile(std::string filename)
{

    // ifstream is used for reading files
    // We'll read from a file called Sample.txt
    std::ifstream inf{filename};

    // If we couldn't open the input file stream for reading
    if (!inf)
    {
        // Print an error and exit
        std::cerr << "Uh oh, " << filename << " could not be opened for reading!\n";
        return false;
    }

    // While there's still stuff left to read
    while (inf)
    {
        // read stuff from the file into a string and print it
        std::string line;
        std::getline(inf, line);
        std::cout << line << std::endl;
    }

    return true;

    // When inf goes out of scope, the ifstream
    // destructor will close the file
}

int main()
{
    std::string filename = "Sample.txt";
    std::vector<std::string> text1 = {"This is line 1", "Line 2", "And line 3"};

    if (!writeTextToFile(filename, text1))
    {
        std::cerr << "Write operation failed." << std::endl;
    }

    if (!appendTextToFile(filename, text1))
    {
        std::cerr << "Append operation failed." << std::endl;
    }

    if (!readTextFromFile(filename))
    {
        std::cerr << "Read operation failed." << std::endl;
    }
}