#include "Data.h"
#include <iostream>
#include <vector>
#include <sstream> //stringstream
#include <regex>
#include <iomanip> // setfill setw
#include <cmath>   // round
#include <fstream> // ifstream

/////////////////////////////////////////////////////////
/// auxiliary function: split a string by a separator

std::vector<std::string> split(const std::string str,
                               const std::string regex_str)
{
    std::regex regexz(regex_str);
    return {std::sregex_token_iterator(str.begin(), str.end(), regexz, -1),
            std::sregex_token_iterator()};
}

/////////////////////////////////////////////////////////
/// auxiliary function: format a (double) time in seconds to string "mm:ss.ms"

std::string format_time(double t_secs)
{
    int mins = (int)floor(t_secs) / 60;
    double secs = t_secs - 60.0 * mins;
    std::stringstream ss;
    ss << std::setfill('0') << std::setw(2) << mins;
    ss.precision(2);
    ss << ":" << std::setfill('0') << std::setw(5) << std::fixed << secs;
    return ss.str();
}

/////////////////////////////////////////////////////////
/// auxiliary function: format a vector for printing

std::string print_vector(std::vector<double> vector,
                         std::string separator = " ",
                         bool highlight = false)
{
    std::string MIN_FORMAT = "\033[1;32m"; // bold green
    std::string MAX_FORMAT = "\033[1;31m"; // bold red
    std::string RESET_FORMAT = "\033[0m";

    auto [min, max] = std::minmax_element(std::begin(vector),
                                          std::end(vector));

    std::string str = " ";
    for (int i = 0; i < vector.size(); i++)
    {
        // here if highlight && min or max -> add color

        if (highlight && vector[i] == *min)
            str += (MIN_FORMAT +
                    format_time(vector[i]) +
                    RESET_FORMAT);
        else if (highlight && vector[i] == *max)
            str += (MAX_FORMAT +
                    format_time(vector[i]) +
                    RESET_FORMAT);
        else
            str += format_time(vector[i]);

        if (i < vector.size() - 1)
            str += separator;
    }
    return str + " ";
}

Data::Data(int id,
           std::string first_name,
           std::string last_name,
           std::vector<double> t_secs,
           double t_avg_secs,
           double t_min_secs) : id(id),
                                first_name(first_name),
                                last_name(last_name),
                                t_secs(t_secs),
                                t_avg_secs(t_avg_secs),
                                t_min_secs(t_min_secs) {}

Data::~Data()
{
}

void Data::show()
{
    std::cout << "ID: " << id << std::endl;
    std::cout << "User: " << first_name << " " << last_name << std::endl;
    std::cout << "Times: " << print_vector(t_secs) << std::endl;
    std::cout << "Average: " << format_time(t_avg_secs) << std::endl;
    std::cout << "Best: " << format_time(t_min_secs) << std::endl;
}

void Data::showtable()
{
    std::cout << "| " << std::setfill('0') << std::setw(3) << id << std::flush;
    std::string full_name = last_name + ", " + first_name;
    std::cout << " | " << std::setfill(' ') << std::setw(20) << full_name << std::flush;
    std::cout << " | " << print_vector(t_secs, " ' ", true) << std::flush;
    std::string AVG_FORMAT = "\033[1;34m"; // bold blue
    std::string RESET_FORMAT = "\033[0m";
    std::cout << " | " << AVG_FORMAT << format_time(t_avg_secs) << RESET_FORMAT << " |" << std::endl;
}

bool readFromFile(std::string filename, std::vector<Data> &dataset)
{

    // ifstream is used for reading files
    std::ifstream inf{filename};

    // If we couldn't open the input file stream for reading
    if (!inf)
    {
        // Print an error
        std::cerr << "Uh oh, " << filename << " could not be opened for reading!\n";
        return false;
    }

    // skip header
    std::string header;
    std::getline(inf, header);

    // While there's still stuff left to read
    while (inf)
    {
        // read from the file into a string and print it
        std::string line;
        std::getline(inf, line);

        if (!line.empty()) // without this segmentation fault. Looks like end of file generates a line
        {
            std::vector<std::string> items;
            std::stringstream line_stream(line);
            std::string item;

            while (getline(line_stream, item, ','))
            {
                items.push_back(item);
            }

            int id = stoi(items[0]); // convert std::string to int
            std::string first_name = items[1];
            std::string last_name = items[2];
            std::vector<double> t_secs;
            for (int i = 3; i < items.size(); i++)
            {
                // process here DNF
                std::vector<std::string> time = split(items[i], ":");
                double mins = std::stod(time[0]);
                double secs = std::stod(time[1]);
                t_secs.push_back(mins * 60.0 + secs);
            }

            auto [min, max] = std::minmax_element(std::begin(t_secs),
                                                  std::end(t_secs));
            double t_max_secs = *min;
            double t_min_secs = *max;

            // average discarding min and max
            double t_avg_secs = 0;
            for (int i = 0; i < t_secs.size(); i++)
            {
                if (t_secs[i] != t_min_secs && t_secs[i] != t_max_secs)
                {
                    t_avg_secs += t_secs[i];
                }
            }

            t_avg_secs /= (t_secs.size() - 2);

            Data data_item(id, first_name, last_name, t_secs, t_avg_secs, t_min_secs);

            // debug
            // std::cout << line << std::endl;
            // data_item.showtable();

            dataset.push_back(data_item);
        }
    }
    // the ifstream destructor closes the file when inf goes out of scope

    return true;
}