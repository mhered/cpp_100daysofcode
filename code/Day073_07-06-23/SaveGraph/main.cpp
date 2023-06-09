#include "iograph.hpp"
#include <iostream>
#include <vector>

int main()
{
    std::vector<std::vector<double>> NodeCoordinates;
    std::vector<std::vector<bool>> Adjacency;

    example_3(NodeCoordinates,
              Adjacency);

    save_to_file("example3.graph", NodeCoordinates, Adjacency);

    std::vector<std::vector<double>> NodeCoordinates2;
    std::vector<std::vector<bool>> Adjacency2;

    read_from_file("example3.graph", NodeCoordinates2, Adjacency2);

    std::string msg = (NodeCoordinates2 == NodeCoordinates) ? "Yes" : "No";
    std::cout << "Check NodeCoordinates read/write is ok? " << msg << std::endl;
    msg = (Adjacency2 == Adjacency) ? "Yes" : "No";
    std::cout << "Adjacency read/write is ok? " << msg << std::endl;

    return 0;
}