#include <cmath> // for sqrt() function
#include <iostream>

// square root function
double mySqrt(double x)
{
    // throw exception if called with a negative number
    if (x < 0.0)
    {
        // throw exception of type const char*
        throw "Can not take sqrt of negative number";
    }
    return std::sqrt(x);
}

void subProcessD() // called by subProcessC()
{
    std::cout << "Start subProcessD\n";
    std::cout << "subProcessD throwing int exception\n";

    throw -1;

    std::cout << "End subProcessD\n"; // skipped over
}

void subProcessC() // called by subProcessB()
{
    std::cout << "Start subProcessC\n";
    subProcessD();
    std::cout << "End subProcessC\n";
}

void subProcessB() // called by ProcessA()
{
    std::cout << "Start subProcessB\n";

    try
    {
        subProcessC();
    }
    catch (double) // not caught: exception type mismatch
    {
        std::cerr << "subProcessB caught double exception\n";
    }

    try
    {
    }
    catch (int) // not caught: exception not thrown within try
    {
        std::cerr << "subProcessB caught int exception\n";
    }

    std::cout << "End subProcessB\n";
}

void ProcessA() // called by main()
{
    std::cout << "Start ProcessA\n";

    try
    {
        subProcessB();
    }
    catch (int) // int exception caught here and handled
    {
        std::cerr << "ProcessA caught int exception\n";
    }

    std::cout << "End ProcessA\n";
}

void saveState()
{
    std::cout << "Terminating gracefully\n";
}

int main()
{
    std::cout << "Start main\n";

    try
    {
        ProcessA();
    }
    catch (int) // not called because exception was handled by A
    {
        std::cerr << "main caught int exception\n";
    }
    catch (...)
    {
        std::cerr << "Abnormal termination\n";
    }

    // terminate gracefully
    saveState();
    std::cout << "End main\n";

    // second part
    double x{};

    while (true)
    {
        std::cout << "Square root calculator. Enter a number (>=0): ";
        std::cin >> x;
        try // Look for exceptions that occur within try block and route to attached catch block(s)
        {
            double d = mySqrt(x);
            // Otherwise, print the answer
            std::cout << "The sqrt of " << x << " is " << d << '\n';
        }
        catch (const char *exception) // catch exceptions of type const char*
        {
            std::cerr << "Error: " << exception << '\n';
        }
    }
}