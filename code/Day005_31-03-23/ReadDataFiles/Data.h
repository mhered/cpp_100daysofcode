#ifndef DATA_H
#define DATA_H

#pragma once

#include <string>

class Data
{
private:
    int id;
    std::string first_name;
    std::string last_name;
    std::string birthdate;
    std::string gender;
    double score;

public:
    Data();
    Data(int id,
         std::string first_name,
         std::string last_name,
         std::string birthdate,
         std::string gender,
         double score);
    ~Data();

    void show();
    bool readFromFile(std::string filename);
    /*
    // setters
    void set_id(int id) { this->id = id; };
    void set_first_name(std::string first_name) { this->first_name = first_name; };
    void set_last_name(std::string last_name) { this->last_name = last_name; };
    void set_birthdate(std::string birthdate) { this->birthdate = birthdate; };
    void set_gender(std::string gender) { this->gender = gender; };
    void set_score(double score) { this->score = score; };
    // getters
    int get_id() { return id; };
    std::string get_first_name() { return first_name; };
    std::string get_last_name() { return last_name; };
    std::string get_birthdate() { return birthdate; };
    std::string get_gender() { return gender; };
    double get_score() { return score; };
    */
};

#endif