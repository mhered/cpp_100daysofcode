#ifndef MINILOGGER_H
#define MINILOGGER_H

//// Mini logger facility
/*

Usage:
#include "minilogger.hpp"

int main()
{
    INFO << "This is an INFO message" << std::endl;
    ERROR << "This is an ERROR message" << std::endl;
    DEBUG << "This is a DEBUG message" << std::endl;
}

Sample output:
2023-06-07 10:21:50 [INFO] main.cpp(main:6) >> This is an INFO message
2023-06-07 10:21:50 [ERROR] main.cpp(main:7) >> This is an ERROR message
2023-06-07 10:21:50 [DEBUG] main.cpp(main:8) >> This is a DEBUG message

Advantages: 
- quickly provides timestamp, file and line
Disadvantages:
- not easy to disable 
- not easy to set debug levels
*/




#include <ctime>
#include <iomanip>

#define __FILENAME__ (__builtin_strrchr(__FILE__, '/') ? __builtin_strrchr(__FILE__, '/') + 1 : __FILE__) // only show filename and not it's path (less clutter)
#define ERROR std::cout << std::put_time(std::localtime(&time_now), "%F %T") << " [ERROR] " << __FILENAME__ << "(" << __FUNCTION__ << ":" << __LINE__ << ") >> "
#define INFO std::cout << std::put_time(std::localtime(&time_now), "%F %T") << " [INFO] " << __FILENAME__ << "(" << __FUNCTION__ << ":" << __LINE__ << ") >> "
#define DEBUG std::cout << std::put_time(std::localtime(&time_now), "%F %T") << " [DEBUG] " << __FILENAME__ << "(" << __FUNCTION__ << ":" << __LINE__ << ") >> "

static std::time_t time_now = std::time(nullptr);

#endif