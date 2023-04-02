#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>

void print_vector(std::vector<uint> vec)
{
    for (auto elem : vec)
        std::cout << elem << ' ';
    std::cout << std::endl;
}

std::string make_column(uint n_times, const char symbol, uint nrows)
{
    // fill with symbol
    std::string col(n_times + 1, symbol);

    // pad to nrows with spaces
    if (col.size() < nrows)
        col += std::string(nrows - col.size(), ' ');

    return col;
}

void plot_skyline(std::vector<uint> skyline)
{

    //     _
    //   _|_|_   _
    //  |_|_|_|_|_|
    // _|_|_|_|_|_|_
    //   2 3 2 1 2

    const char floor = '_';
    const char wall = '|';

    uint nrows = *max_element(skyline.begin(), skyline.end()) + 2;

    // build canvas_transposed column-wise from left to right
    std::vector<std::string> canvas_transposed;

    // first column of walls
    canvas_transposed.push_back(make_column(1, floor, nrows));
    canvas_transposed.push_back(make_column(skyline[0], wall, nrows));

    for (uint i = 0; i < skyline.size(); i++)
    {
        // add column of floors
        canvas_transposed.push_back(make_column(skyline[i] + 1, floor, nrows));

        if (i < skyline.size() - 1)
        {
            // add column of walls
            canvas_transposed.push_back(make_column(std::max(skyline[i], skyline[i + 1]), wall, nrows));
        }
    }
    // last column of walls
    canvas_transposed.push_back(make_column(skyline[skyline.size() - 1], wall, nrows));
    canvas_transposed.push_back(make_column(1, floor, nrows));

    /*
    // plot transposed
    for (int i = canvas_transposed[0].size(); i > 0; --i)
    {
        for (auto line : canvas_transposed)
        {
            std::cout << line[i] << std::flush;
        }
        std::cout << std::endl;
    }
    */

    // transpose
    // initialize canvas
    std::vector<std::string> canvas;
    for (uint i = 0; i < canvas_transposed[0].size(); i++)
    {
        std::string row(canvas_transposed.size(), '*');
        canvas.push_back(row);
    }
    // copy transpose
    for (uint i = 0; i < nrows; i++)
    {
        for (uint j = 0; j < canvas_transposed.size(); j++)
        {
            canvas[i][j] = canvas_transposed[j][nrows - i];
        }
    }
    // plot
    // Header
    std::cout << "W" << std::string(2 * skyline.size() + 1, ' ') << "E" << std::endl;
    // skyline
    for (auto line : canvas)
    {
        std::cout << line << std::endl;
    }
    // footer
    std::cout << "  " << std::flush;
    print_vector(skyline);
    std::cout << std::endl;
}

std::vector<uint> search_apartment(std::vector<uint> skyline, char direction)
{
    std::vector<uint> has_view(skyline.size(), 1);

    plot_skyline(skyline);

    if (toupper(direction) == 'W')
    {

        for (uint i = 0; i < skyline.size(); i++)
        {
            for (uint j = 0; j < i; j++)
            {
                if (skyline[j] >= skyline[i])
                {
                    has_view[i] = 0;
                    break;
                }
            }
        }
    }

    if (toupper(direction) == 'E')
    {

        for (uint i = 0; i < skyline.size(); i++)
        {
            uint start_scan = i + 1;
            uint end_scan = skyline.size();
            for (uint j = start_scan; j < end_scan; j++)
            {
                if (skyline[j] >= skyline[i])
                {
                    has_view[i] = 0;
                    break;
                }
            }
        }
    }

    std::cout << "  " << std::flush;
    print_vector(has_view);
    std::cout << std::endl;

    // build return vector with positions of building with a view
    std::vector<uint> result;
    for (uint i = 0; i < has_view.size(); i++)
        if (has_view[i])
            result.push_back(i);
    return result;
}

int main()
{

    print_vector(search_apartment({3, 5, 4, 4, 7, 1, 3, 2}, 'W')); // {0, 1, 4}
    print_vector(search_apartment({3, 5, 4, 4, 7, 1, 3, 2}, 'E')); // {4, 6, 7}
    print_vector(search_apartment({1, 1, 1, 1, 1, 2}, 'W'));       // {0, 5}
    print_vector(search_apartment({1, 1, 1, 1, 1, 2}, 'E'));       // {5}

    print_vector(search_apartment({3, 5, 4, 3, 3, 1}, 'W')); // {0, 1}
    print_vector(search_apartment({3, 5, 4, 3, 3, 1}, 'E')); // {1, 2, 4, 5}
    print_vector(search_apartment({1, 1, 1, 1, 1}, 'W'));    // {0}
    print_vector(search_apartment({2, 1, 1, 1, 1}, 'E'));    // {0, 4}

    return 0;
}