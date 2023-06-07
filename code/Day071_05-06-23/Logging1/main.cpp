#include <iostream>
#include "minilogger.hpp"

int main()
{
    INFO << "This is an INFO message" << std::endl;
    ERROR << "This is an ERROR message" << std::endl;
    DEBUG << "This is a DEBUG message" << std::endl;

    return 0;
}