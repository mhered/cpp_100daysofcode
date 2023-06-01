#include "utils.h"
#include "File.h"

File::~File()
{
}

bool File::analyze_file()
{
    bool verbose = false;
    // ifstream is used for reading files
    std::ifstream inf{filename};

    // If we couldn't open the input file stream for reading
    if (!inf)
    {
        // Print an error and exit
        std::cerr << "File " << filename << " could not be opened for reading!\n";
        return false;
    }

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

    if (verbose)
    {
        std::cout << "Total lines of code: " << count_total_lines << std::endl;
        std::cout << "of which: " << std::endl;
        std::cout << count_code_lines << " code lines" << std::endl;
        std::cout << count_comment_lines << " comment lines" << std::endl;
        std::cout << count_blank_lines << " blank lines" << std::endl;
        std::cout << std::endl;
    }

    return (count_total_lines == (count_code_lines + count_comment_lines + count_blank_lines));
}
