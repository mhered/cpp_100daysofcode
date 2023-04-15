#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>

bool formatAsGtest(std::string filename)
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

    const std::string delim1 = "It(";
    const std::string delim2 = "Assert::That(";
    const std::string delim3 = "), Equals(";
    const std::string delim4 = "));}";
    std::string line = "";
    std::string token1 = "";
    std::string token2 = "";

    std::cout << "INSTANTIATE_TEST_CASE_P(Default, CarsTest," << std::endl;
    std::cout << "  testing::Values(" << std::endl;

    // While there's still stuff left to read
    while (inf)
    {
        std::getline(inf, line);
        // std::cout << line << std::endl;
        if (line.rfind(delim1, 0) == 0)
        {
            uint pos1 = line.find(delim2) + delim2.size();
            uint len1 = line.find(delim3) - pos1;
            token1 = line.substr(pos1, len1);

            uint pos11 = token1.find('(') + 1;
            token1 = token1.substr(pos11, token1.size() - pos11);

            uint pos2 = line.find(delim3) + delim3.size();
            uint len2 = line.find(delim4) - pos2;
            token2 = line.substr(pos2, len2);

            std::cout << "      Sample({ " << token1 << " }, " << token2 << ")," << std::endl;
        }
    }
    std::cout << "      ));" << std::endl;

    return true;

    // When inf goes out of scope, the ifstream
    // destructor will close the file
}

bool formatAsCout(std::string filename)
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

    const std::string delim1 = "It(";
    const std::string delim2 = "Assert::That(";
    const std::string delim3 = ", Equals(";
    const std::string delim4 = "));}";
    std::string line = "";
    std::string token1 = "";
    std::string token2 = "";

    // While there's still stuff left to read
    while (inf)
    {
        std::getline(inf, line);
        // std::cout << line << std::endl;
        if (line.rfind(delim1, 0) == 0)
        {
            uint pos1 = line.find(delim2) + delim2.size();
            uint len1 = line.find(delim3) - pos1;
            token1 = line.substr(pos1, len1);

            uint pos2 = line.find(delim3) + delim3.size();
            uint len2 = line.find(delim4) - pos2;
            token2 = line.substr(pos2, len2);

            std::cout << "std::cout << " << token1 << " << std::endl; // " << token2 << std::endl;
        }
    }

    return true;

    // When inf goes out of scope, the ifstream
    // destructor will close the file
}

int main()
{
    std::string filename = "Tests.txt";

    if (!formatAsGtest(filename))
    {
        std::cerr << "Read operation failed." << std::endl;
    }

    if (!formatAsCout(filename))
    {
        std::cerr << "Read operation failed." << std::endl;
    }
}