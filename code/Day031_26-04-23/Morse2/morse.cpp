#include <string>
#include <iostream>
#include <vector>
#include "myutils.h"

bool send_arduino(std::string msg)
{

    return true;
}

bool send(std::string msg)
{
    msg = preprocess(msg);
    std::string morse_msg = translate(msg, true);
    std::string ones_zeroes = translate2(morse_msg, true);

    if (send_arduino(morse_msg))
    {
        std::cout << "Sent Message: \"" << msg << "\"" << std::endl;
        return true;
    }
    return false;
}

void help()
{
    std::string msg = "morse- A simple CLI so send Morse messages through Arduino\n\n";
    msg += "Usage: ./morse {message}\n\n";
    msg += "Available commands:\n\n";
    msg += "   $ ./morse (-h)              - display this help\n";
    msg += "   $ ./morse -s \"Message\"  - send Message in morse\n";

    std::cout << msg << std::endl;
}

int main(int argc, char *argv[])
{
    // declare variables
    std::string Command, Parameter;
    int k = 0;

    if (argc > 1)
        Command = argv[1];

    if (argc == 1 || Command == "-h") // display help
    {
        help();
    }
    else if (Command == "-s")
    {
        if (argc == 2)
        {
            std::cout << "ERROR: missing Message string. Nothing was sent." << std::endl;
            help();
        }
        else
        {
            Parameter = argv[2];
            send(Parameter);
        }
    }
    return 0;
}
