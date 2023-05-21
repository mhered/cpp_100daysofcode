#include <iostream>
#include <iomanip>
#include <sstream>

void fg_256_colors()
{
    for (int i = 0; i < 16; i++)
    {
        for (int j = 0; j < 16; j++)
        {
            int code = i * 16 + j;
            std::cout << "\033[38;5;" << code << "m " << std::setw(4) << std::left << std::to_string(code);
        }
        std::cout << "\033[0m" << std::endl;
    }
}

void bkg_256_colors()
{
    for (int i = 0; i < 16; i++)
    {
        for (int j = 0; j < 16; j++)
        {
            int code = i * 16 + j;
            std::cout << "\033[48;5;" << code << "m " << std::setw(4) << std::left << std::to_string(code); //.append(4 - std::to_string(code).length(), ' ');
        }
        std::cout << "\033[0m" << std::endl;
    }
}

void fg_true_colors()
{
    for (int r = 0; r < 256; r += 32)
    {
        for (int g = 0; g < 256; g += 32)
        {
            for (int b = 0; b < 256; b += 32)
            {
                std::stringstream ss;
                ss << "[" << std::setw(3) << std::left << std::to_string(r) << ",";
                ss << std::setw(3) << std::left << std::to_string(g) << ",";
                ss << std::setw(3) << std::left << std::to_string(b) << "]";
                std::cout << "\033[38;2;" << r << ";" << g << ";" << b << "m " << ss.str();
            }
            std::cout << "\033[0m" << std::endl;
        }
    }
}
int main()
{
    fg_256_colors();
    bkg_256_colors();
    fg_true_colors();
}