#include <iostream>
#include "logger.hpp"

// define log level
logLevel loglevel = logDEBUG2;

void logTest(void)
{
    logLevel loglevel_save = loglevel;

    log(logINFO) << "foo "
                 << "bar ";

    log(logWARNING) << "baz";

    int count = 3;
    log(logDEBUG) << "A loop with " << count << " iterations";
    for (int i = 0; i != count; ++i)
    {
        log(logDEBUG1) << "the counter i = " << i;
        log(logDEBUG2) << "the counter i = " << i;
    }

    loglevel = loglevel_save;
}

int main()

{
    std::cout << "logLevel = " << loglevel << std::endl;
    logTest();
    return 0;
}