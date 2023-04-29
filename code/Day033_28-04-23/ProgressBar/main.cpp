#include <iostream>
#include <chrono>
#include <thread>
#include <iomanip> // setw() padding

void ProgressBar(float &progress, std::string Title = "Progress", int barWidth = 40)
{

    if (progress < 1.0)
        std::cout << std::setw(Title.length()) << Title;
    else
        std::cout << std::setw(Title.length()) << "Done";

    std::cout << std::setw(5) << int(progress * 100.0) << "% [";
    int pos = barWidth * progress;
    for (int i = 0; i < barWidth; ++i)
    {
        if (i <= pos)
            std::cout << "|";
        else
            std::cout << " ";
    }

    if (progress < 1.0)
    {
        std::cout << "] \r";
        std::cout.flush();
    }
    else
        std::cout << "]" << std::endl;
}

int main()
{

    float progress = 0.0;
    float increment = 0.01;
    do
    {
        // for demonstration: a slow process that regularly updates progress
        progress += increment;
        std::this_thread::sleep_for(std::chrono::milliseconds(40));
        ProgressBar(progress);

    } while (progress < 1.0);
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    return 0;
}