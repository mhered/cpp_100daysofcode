#include <iostream>
#include "Data.h"

#include <fstream>
#include <vector>

// for CSV
#include <sstream>

// for JSON
#include <iomanip>
#include <nlohmann/json.hpp>

// for XML
#include <rapidxml/rapidxml.hpp>
#include <string.h>
#include <stdio.h>

std::vector<Data> readCSV(std::string filename)
{
    std::vector<Data> dataset;

    // ifstream is used for reading files
    std::ifstream inf{filename};

    // If we couldn't open the input file stream for reading
    if (!inf)
    {
        // Print an error
        std::cerr << "Uh oh, " << filename << " could not be opened for reading!\n";
        return dataset; // no exception handling!!
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
            std::string birthdate = items[3];
            std::string gender = items[4];
            double score = std::stod(items[5]);
            dataset.push_back(Data(id, first_name, last_name, birthdate, gender, score));
        }
    }
    // the ifstream destructor close the file when inf goes out of scope

    return dataset;
}

std::vector<Data> readJSON(std::string filename)
{
    std::vector<Data> dataset;

    // load contents of JSON file
    std::ifstream f(filename);
    nlohmann::json data = nlohmann::json::parse(f);

    // show contents
    // setw(4) to pretty print, requires <iomanip>
    // std::cout << std::setw(4) << data << std::endl;

    for (auto item : data)
    {
        int id = item["id"]; // auto conversion to int
        std::string first_name = item["first_name"];
        std::string last_name = item["last_name"];
        std::string birthdate = item["birthdate"];
        std::string gender = item["gender"];
        double score = item["score"]; // auto conversion to double
        dataset.push_back(Data(id, first_name, last_name, birthdate, gender, score));
    }

    return dataset;
}

std::vector<Data> readXML(std::string filename)
{
    std::vector<Data> dataset;

    rapidxml::xml_document<> doc;
    rapidxml::xml_node<> *root_node;

    std::cout << "Parsing the XML file..." << std::endl;

    // Read the xml file into a vector
    std::ifstream f(filename);
    std::vector<char> buffer((std::istreambuf_iterator<char>(f)), std::istreambuf_iterator<char>());
    buffer.push_back('\0');

    // Parse the buffer using the xml file parsing library into doc
    doc.parse<0>(&buffer[0]);

    // Find the root node
    root_node = doc.first_node("dataset");

    // Iterate over the records
    for (rapidxml::xml_node<> *record_node = root_node->first_node("record");
         record_node;
         record_node = record_node->next_sibling())
    {
        // Get values from nodes inside the record
        int id = atoi(record_node->first_node("id")->value()); // convert char* to int
        std::string first_name = record_node->first_node("first_name")->value();
        std::string last_name = record_node->first_node("last_name")->value();
        std::string birthdate = record_node->first_node("birthdate")->value();
        std::string gender = record_node->first_node("gender")->value();
        double score = std::stod(record_node->first_node("score")->value()); // convert to double
        dataset.push_back(Data(id, first_name, last_name, birthdate, gender, score));
    }

    return dataset;
}

int main()
{
    bool repeat = true;
    std::string filename;
    std::vector<Data> dataset;

    std::cout << "Please select which sample file you want to read (1-3 or Q to quit):" << std::endl;
    std::cout << "1. CSV (MOCK_DATA.csv)" << std::endl;
    std::cout << "2. JSON (MOCK_DATA.json)" << std::endl;
    std::cout << "3. XML (dataset.xml)" << std::endl;

    do
    {
        char option;
        std::cin >> option;

        switch (tolower(option))
        {
        case '1':
            filename = "MOCK_DATA.csv";
            dataset = readCSV(filename);
            repeat = false;
            break;
        case '2':
            filename = "MOCK_DATA.json";
            dataset = readJSON(filename);
            repeat = false;
            break;
        case '3':
            filename = "dataset.xml";
            dataset = readXML(filename);
            repeat = false;
            break;
        case 'q':
            std::cout << "Bye" << std::endl;
            return 0;
        default:
            std::cout << "Invalid input. Please select 1-3 or Q to quit" << std::endl;
        };

    } while (repeat);

    if (!dataset.empty())
    {
        for (auto elem : dataset)
            elem.show();

        std::cout << std::endl;
        std::cout << dataset.size() << " records successfully read from the file: " << filename << std::endl;
        std::cout << std::endl;
        return 0;
    }
    else
        return 1;
}