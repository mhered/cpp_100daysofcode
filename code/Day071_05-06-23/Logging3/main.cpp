#include <iostream>
#include "logger.hpp"

int main()
{
    Logger logger("");
    logger.setLevel(LogLevel::DEBUG);
    ERROR(logger, "Error message");
    WARNING(logger, "Warning message");
    INFO(logger, "Info message");
    DEBUG(logger, "Debug message");

    return 0;
}
