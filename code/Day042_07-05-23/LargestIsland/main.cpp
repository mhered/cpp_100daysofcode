#include <iostream>
#include <vector>
#include <algorithm>

const static int SEA = 0;
const static int UNEXPLORED = 1;
const static int EXPLORING = 2;
const static int EXPLORED = 4;

void show_map(std::vector<std::vector<int>> arr)
{
    std::cout << "Map: \n";
    for (int i = 0; i < arr.size(); i++)
    {
        for (int j = 0; j < arr[0].size(); j++)
        {
            std::cout << arr[i][j] << " ";
        }
        std::cout << "\n";
    }
    std::cout << std::endl;
    ;
}

int explore_neighbors(std::vector<std::vector<int>> &map, int i0, int j0, bool verbose = false)
{
    int count = 0;
    int nrows = map.size();
    int ncols = map[0].size();

    std::vector<std::pair<int, int>> to_explore;
    for (int di = -1; di <= 1; di++)
    {
        for (int dj = -1; dj <= 1; dj++)
        {
            int i = i0 + di;
            int j = j0 + dj;
            if (i >= 0 && i < nrows && j >= 0 && j < ncols) // search valid neighbors
            {
                if (map[i][j] == UNEXPLORED) // when unexplored pixel found
                {
                    if (verbose)
                        std::cout << "Found unexplored(" << i << ", " << j << ")" << std::endl;
                    map[i][j] = EXPLORED; // mark as explored
                    count += 1;
                    if (verbose)
                        show_map(map);
                    count += explore_neighbors(map, i, j); // recurse
                }
            }
        }
    }
    return count;
}

int largestIsland(std::vector<std::vector<int>> map, bool verbose = false)
{
    int nrows = map.size();
    int ncols = map[0].size();
    int max_size = 0;
    std::vector<int> island_sizes;

    // search for islands
    for (int i = 0; i < nrows; i++)
    {
        for (int j = 0; j < ncols; j++)
        {
            if (map[i][j] == UNEXPLORED)
            {
                // when new island found, explore (recursively)
                int island_size = explore_neighbors(map, i, j);
                // add island to list
                island_sizes.push_back(island_size);
            }
        }
    }

    if (!island_sizes.empty())
    {
        max_size = *std::max_element(island_sizes.begin(), island_sizes.end());
    }

    if (verbose)
    {
        std::cout << "Found: " << island_sizes.size() << " island";
        if (island_sizes.size() != 1)
            std::cout << "s";
        std::cout << " in " << nrows << " x " << ncols << " map.";
        std::cout << " Largest island has area: " << max_size << std::endl;
    }
    return max_size;
}

int main()
{
    std::vector<std::vector<int>> map;
    map = {
        {0, 1, 0, 1},
        {1, 0, 1, 0},
        {0, 1, 0, 1},
        {1, 0, 1, 0}}; // Found: 1 island in 4 x 4 map. Largest island has area: 8

    map = {
        {1, 1, 0, 0, 1, 1, 0},
        {0, 1, 0, 0, 0, 1, 0},
        {1, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 1, 0, 1, 0},
        {0, 0, 1, 1, 1, 1, 0},
        {0, 1, 0, 1, 0, 1, 0}}; // Found: 3 islands in 6 x 6 map. Largest island has area: 8

    map = {
        {1, 0, 0, 0, 1, 1},
        {0, 0, 1, 1, 1, 0},
        {0, 0, 0, 0, 0, 0},
        {0, 0, 1, 1, 1, 0},
        {0, 0, 1, 1, 1, 0},
        {0, 0, 0, 0, 0, 0},
        {0, 0, 1, 1, 0, 0},
        {0, 0, 0, 0, 0, 0},
        {1, 0, 0, 0, 0, 1}}; // Found: 6 islands in 9 x 6 map. Largest island has area: 6
    /*
        map = {
               {0, 0, 0, 0, 0, 0},
               {0, 0, 0, 0, 0, 0},
               {0, 0, 0, 0, 0, 0},
               {0, 0, 0, 0, 0, 0}}; // Found: 0 islands in 4 x 6 map. Largest island has area: 0

        map = {
               {0, 0, 0, 0, 0},
               {0, 1, 1, 1, 0},
               {0, 1, 0, 1, 0},
               {0, 1, 1, 1, 0},
               {0, 0, 0, 0, 0}}; // Found: 1 island in 5 x 5 map. Largest island has area: 8
    */
    show_map(map);

    int max_size = largestIsland(map, true);

    return 0;
}