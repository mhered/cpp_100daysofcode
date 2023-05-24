#include <iostream>
#include <fstream>
#include <algorithm> //all_of

#include <cstring>  // strcmp
#include <sstream> //stringstream

#include <cctype>
#include <locale>

// #include "colors.h" // defines color macros

std::string LINE_COMMENT = "//";
std::string START_BLOCK_COMMENT = "/*";
std::string END_BLOCK_COMMENT = "*/";

const std::string RED("\033[0;31m");
const std::string GREEN("\033[0;32m");
const std::string BLUE("\033[0;34m");
const std::string YELLOW("\033[0;33m");
const std::string CYAN("\033[0;36m");
const std::string MAGENTA("\033[0;35m");
const std::string RESET("\033[0m");

// trim from start (in place)
static inline void ltrim(std::string &s)
{
    s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](unsigned char ch)
                                    { return !std::isspace(ch); }));
}

// trim from end (in place)
static inline void rtrim(std::string &s)
{
    s.erase(std::find_if(s.rbegin(), s.rend(), [](unsigned char ch)
                         { return !std::isspace(ch); })
                .base(),
            s.end());
}

// trim from both ends (in place)
static inline void trim(std::string &s)
{
    rtrim(s);
    ltrim(s);
}

// trim from start (copying)
static inline std::string ltrim_copy(std::string s)
{
    ltrim(s);
    return s;
}

// trim from end (copying)
static inline std::string rtrim_copy(std::string s)
{
    rtrim(s);
    return s;
}

// trim from both ends (copying)
static inline std::string trim_copy(std::string s)
{
    trim(s);
    return s;
}

bool endswith(std::string s, std::string suffix)
{
    return s.find(suffix, s.length() - suffix.length()) != std::string::npos;
}

bool startswith(std::string s, std::string prefix)
{
    return (s.rfind(prefix, 0) == 0);
}

bool is_blank_line(std::string str)
{
    return std::all_of(str.begin(), str.end(), isspace);
}

bool starts_with_line_comment(std::string str)
{
    ltrim(str);
    return startswith(str, LINE_COMMENT);
}

bool block_comment_starts(std::string str)
{
    ltrim(str);
    return startswith(str, START_BLOCK_COMMENT);
}

bool block_comment_ends(std::string str)
{
    rtrim(str);
    return endswith(str, END_BLOCK_COMMENT);
}

bool analyze_file(std::string filename, bool verbose = false)
{

    // ifstream is used for reading files
    std::ifstream inf{filename};

    // If we couldn't open the input file stream for reading
    if (!inf)
    {
        // Print an error and exit
        std::cerr << "File " << filename << " could not be opened for reading!\n";
        return false;
    }

    uint count_total_lines = 0;
    uint count_code_lines = 0;
    uint count_blank_lines = 0;
    uint count_comment_lines = 0;

    // While there's still stuff left to read
    while (inf)
    {
        // read line from the file into a string and print it
        std::string line;
        std::getline(inf, line);
        count_total_lines++;
        if (is_blank_line(line)) // if only whitespace -> blank
        {
            count_blank_lines++;
            if (verbose)
                std::cout << YELLOW << "  BLANK: " << line << RESET << std::endl;
        }
        else if (starts_with_line_comment(line)) // if starts by // -> comment, skip
        {
            count_comment_lines++;
            if (verbose)
                std::cout << GREEN << "COMMENT: " << line << RESET << std::endl;
        }
        else if (block_comment_starts(line)) // if starts by /* -> comment, keep skipping until */ found
        {
            count_comment_lines++;
            if (verbose)
                std::cout << GREEN << "COMMENT: " << line << RESET << std::endl;
            while (!block_comment_ends(line))
            {
                std::getline(inf, line);
                count_total_lines++;
                count_comment_lines++;
                if (verbose)
                    std::cout << GREEN << "COMMENT: " << line << RESET << std::endl;
            }
        }
        else // otherwise: code
        {
            count_code_lines++;
            if (verbose)
                std::cout << BLUE << "   CODE: " << line << RESET << std::endl;
        }
    }

    std::cout << "Total lines of code: " << count_total_lines << std::endl;
    std::cout << "of which: " << std::endl;
    std::cout << count_code_lines << " code lines" << std::endl;
    std::cout << count_comment_lines << " comment lines" << std::endl;
    std::cout << count_blank_lines << " blank lines" << std::endl;

    /*std::cout << "Total lines of code: " << count_total_lines << std::endl;
    std::cout << "of which: " << std::endl;
    std::cout << count_code_lines << " code lines" << std::endl;
    std::cout << count_comment_lines << " comment lines" << std::endl;
    std::cout << count_blank_lines << " blank lines" << std::endl;*/

    /*std::cout << "Total lines of code: " << count_total_lines << std::endl;*/
    std::cout << std::endl;
    /*std::cout << "of which: " << std::endl;
    std::cout << count_code_lines << " code lines" << std::endl;*/
    std::cout << std::endl;
    /*std::cout << count_comment_lines << " comment lines" << std::endl;
    std::cout << count_blank_lines << " blank lines" << std::endl;*/

    return true;
}

int main(int argc, char **argv)
{
    bool verbose;

    if (argc > 1)
    {
        std::string filename = argv[1];
        if (argc > 2)
        {
            verbose = std::strcmp(argv[2], "--verbose") == 0;
        }
        if (!analyze_file(filename, verbose))
        {
            std::cerr << "Could not read file \"" << filename << "\"" << std::endl;
            return -1;
        }
    }
    else
        std::cout << "Please provide filename as parameter" << std::endl;
    return 0;
}