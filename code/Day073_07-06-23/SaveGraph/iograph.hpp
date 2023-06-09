#ifndef IOGRAPH_H
#define IOGRAPH_H

#pragma once

#include <iostream>
#include <vector>

#include <fstream>
#include <sstream>
#include <regex>
#include "examples.h"
#include "Graph.h"

bool save_to_file(std::string filename,
                  std::vector<std::vector<double>> NodeCoordinates,
                  std::vector<std::vector<bool>> Adjacency)
{
    std::ofstream outf{filename};

    if (!outf)
    {
        std::cerr << "File " << filename << " could not be opened for writing\n";
        return false;
    }

    outf << NodeCoordinates.size() << "\n\n";

    for (auto node : NodeCoordinates)
    {
        outf << node[0] << " " << node[1] << "\n";
    }
    outf << "\n";
    for (auto row : Adjacency)
    {
        for (auto elem : row)
        {
            outf << elem << " ";
        }
        outf << "\n";
    }

    return true;
}

// auxiliary function: split a string by a separator
std::vector<std::string> split(const std::string str,
                               const std::string regex_str)
{
    std::regex regexz(regex_str);
    return {std::sregex_token_iterator(str.begin(), str.end(), regexz, -1),
            std::sregex_token_iterator()};
}

bool read_from_file(std::string filename,
                    std::vector<std::vector<double>> &NodeCoordinates,
                    std::vector<std::vector<bool>> &Adjacency)
{
    std::ifstream inf{filename};

    // If we couldn't open the input file stream for reading
    if (!inf)
    {
        // Print an error and exit
        std::cerr << "File " << filename << " could not be opened for reading!\n";
        return false;
    }

    std::string line;
    std::getline(inf, line);
    int N = stoi(line); // number of nodes

    std::getline(inf, line); // skip line

    for (int i = 0; i < N; i++)
    {
        std::getline(inf, line);
        std::vector<std::string> coordinates = split(line, " ");
        double x, y;
        x = stod(coordinates[0]);
        y = stod(coordinates[1]);
        NodeCoordinates.push_back({x, y});
    }
    std::getline(inf, line); // skip line

    for (int i = 0; i < N; i++)
    {
        std::getline(inf, line);
        std::vector<std::string> edges = split(line, " ");

        std::vector<bool> row;
        for (int j = 0; j < N; j++)
        {
            row.push_back((bool)stoi(edges[j]));
        }
        Adjacency.push_back(row);
    }
    return true;
}


#endif
