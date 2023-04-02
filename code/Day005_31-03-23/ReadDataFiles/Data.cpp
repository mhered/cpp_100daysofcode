#include "Data.h"
#include <iostream>

Data::Data(int id,
           std::string first_name,
           std::string last_name,
           std::string birthdate,
           std::string gender,
           double score) : id(id),
                           first_name(first_name),
                           last_name(last_name),
                           birthdate(birthdate),
                           gender(gender),
                           score(score) {}

Data::~Data()
{
}

void Data::show()
{
    std::cout << "ID: " << id << std::endl;
    std::cout << "User: " << first_name << " " << last_name << " (" << gender << ")" << std::endl;
    std::cout << "Birth date: " << birthdate << std::endl;
    std::cout << "Score: " << 100*score << "%" << std::endl;
}
