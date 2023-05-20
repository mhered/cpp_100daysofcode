#ifndef DATA_H
#define DATA_H

#pragma once

#include <string>
#include <vector>

class Data
{
private:
    int id;
    std::string first_name;
    std::string last_name;
    std::vector<double> t_secs;
    double t_min_secs;

public:
    double t_avg_secs;
    Data();
    Data(int id,
         std::string first_name,
         std::string last_name,
         std::vector<double> t_secs,
         double t_avg_secs,
         double t_min_secs);

    ~Data();

    void show();
    void showtable();
};

bool readFromFile(std::string filename, std::vector<Data> &dataset);

#endif