#include <iostream>
#include <thread>
#include "kbhit.h"

void display(int N)
{
    int key_nr;
    char key;
    keyboard keyboard;

    while (true)
    {
        if (keyboard.kbhit())
        {
            key_nr = keyboard.getch(); // return int
            key = key_nr;              // get ascii char

            if (key == 'a')
            {
                std::cout << "A has been pressed" << std::endl;
            }
            else if (key == 'q')
            {
                std::cout << "Q has been pressed" << std::endl;
            }
        }
    }
}

int main()
{
    std::thread t1(display, 1);
    std::string data;
    std::cout << "Enter some data: ";
    std::cin >> data;

    t1.join();

    return 0;
}
