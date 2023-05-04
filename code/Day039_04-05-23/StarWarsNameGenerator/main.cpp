#include <iostream>
#include <fstream>
#include <vector>
#include <regex>

// auxiliary function: split a string by a separator
std::vector<std::string> split(const std::string str,
                               const std::string regex_str)
{
    std::regex regexz(regex_str);
    return {std::sregex_token_iterator(str.begin(), str.end(), regexz, -1),
            std::sregex_token_iterator()};
}

bool read_from_file(std::string filename, std::vector<std::string> &tasks)
{

    std::string task;

    std::fstream infile;
    infile.open(filename, std::ios::in);

    if (!infile)
    {
        // If the input file stream cannot be open for reading
        // Print an error and exit
        std::cerr << "ERROR: Could not open " << filename << std::endl;
        return false;
    }
    else
    {
        while (std::getline(infile, task))
        {
            tasks.push_back(task);
        }
    }
    infile.close();
    return true;
}

std::string first_n_chars(std::string str, int n)
{ // no-ref, no-const
    str.resize(n);
    return str;
}

std::string Titlecase(std::string str)
{ // no-ref, no-const
    std::string result;
    for (int i = 0; i < str.size(); i++)
        if (i > 0)
            result.push_back(tolower(str[i]));
        else
            result.push_back(toupper(str[i]));
    return result;
}

int main()
{
    std::vector<std::string> names;
    read_from_file("data.txt", names);
    for (auto name : names)
    {
        std::vector<std::string> parts = split(name, " ");

        std::string first_name = parts[0];
        std::string last_name = parts[1];
        std::string mothers_maiden_name = parts[2];
        std::string birthplace = parts[3];

        std::string first_name_sw = first_n_chars(first_name, 3) +
                                    first_n_chars(last_name, 2);

        std::string last_name_sw = first_n_chars(mothers_maiden_name, 3) +
                                   first_n_chars(birthplace, 3);
        std::cout << first_name << " " << last_name << " -> "
                  << Titlecase(first_name_sw) << " " << Titlecase(last_name_sw) << std::endl;
    }

    return 0;
}