#include <vector>

void example_1(std::vector<std::vector<double>> &NodeCoordinates,
               std::vector<std::vector<bool>> &Adjacency)
{
    NodeCoordinates = {
        {15.0, 8.6603}, // Node 0
        {0.0, 0.0},     // Node 1
        {20.0, 0.0},    // Node 2
        {25.0, 8.6603}, // Node 3
        {10.0, 0.0},    // Node 4
        {5.0, 8.6603}}; // Node 5

    Adjacency = {
        {0, 0, 1, 1, 1, 1},  // Node 0
        {0, 0, 0, 0, 1, 1},  // Node 1
        {0, 0, 0, 1, 1, 0},  // Node 2
        {0, 0, 0, 0, 0, 0},  // Node 3
        {0, 0, 0, 0, 0, 1},  // Node 4
        {1, 0, 0, 0, 0, 0}}; // Node 5
}

void example_2(std::vector<std::vector<double>> &NodeCoordinates,
               std::vector<std::vector<bool>> &Adjacency)
{
    NodeCoordinates = {
        {10.0, 30.0}, // Node 0
        {10.0, 10.0}, // Node 1
        {30.0, 10.0}, // Node 2
        {30.0, 30.0}, // Node 3
        {40.0, 20.0}, // Node 4
    };

    Adjacency = {
        {0, 1, 0, 1, 0},  // Node 0
        {1, 0, 1, 1, 0},  // Node 1
        {0, 1, 0, 1, 1},  // Node 2
        {1, 1, 1, 0, 1},  // Node 3
        {0, 0, 1, 1, 0}}; // Node 4
}

void example_3(std::vector<std::vector<double>> &NodeCoordinates,
               std::vector<std::vector<bool>> &Adjacency)
{
    NodeCoordinates = {
        {18.0, 60.0},   // Node 00
        {38.0, 60.0},   // Node 01
        {20.0, 40.0},   // Node 02
        {40.0, 40.0},   // Node 03
        {40.0, 10.0},   // Node 04
        {60.0, 10.0},   // Node 05
        {85.0, 25.0},   // Node 06
        {80.0, 45.0},   // Node 07
        {73.0, 70.0},   // Node 08
        {105.0, 30.0},  // Node 09
        {100.0, 50.0},  // Node 10
        {95.0, 70.0},  // Node 11
        {90.0, 90.0},  // Node 12
        {125.0, 30.0},  // Node 13
        {120.0, 50.0},  // Node 14
        {110.0, 90.0}}; // Node 15

    Adjacency = {
        {0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, // Node 00
        {1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, // Node 01
        {0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, // Node 02
        {0, 1, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0}, // Node 03
        {0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, // Node 04
        {0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0}, // Node 05
        {0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0}, // Node 06
        {0, 0, 0, 0, 0, 1, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0}, // Node 07
        {0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0}, // Node 08
        {0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0}, // Node 09
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0}, // Node 10
        {0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0}, // Node 11
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1}, // Node 12
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0}, // Node 13
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1}, // Node 14
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0}, // Node 15
    };
}