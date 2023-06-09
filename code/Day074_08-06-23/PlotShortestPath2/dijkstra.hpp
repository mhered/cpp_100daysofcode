#include <iostream>
#include <vector>
#include <algorithm>
#include <sstream>
#include <iomanip>
#include <cmath>
#include "Graph.h"

size_t get_closest_node_from_queue(std::vector<size_t> &prio_queue, double dist[], size_t N)
{
    std::vector<double> distances;
    for (auto node : prio_queue)
    {
        distances.push_back(dist[node]);
    }
    auto it = std::min_element(std::begin(distances), std::end(distances));
    size_t idx = std::distance(std::begin(distances), it);

    size_t elem = prio_queue[idx];
    prio_queue.erase(std::begin(prio_queue) + idx);
    return elem;
}

// auxiliary function to check if vector contains element
bool contains(std::vector<size_t> vec, size_t elem)
{
    bool result = std::find(vec.begin(), vec.end(), elem) != vec.end();
    return result;
}

std::list<size_t> dijkstra(Graph &graph, size_t Source, size_t Target, double *dist)
{
    // initialization
    const double INFINITE = MAXFLOAT;
    const size_t UNEXPLORED = graph.N;

    /*double *dist = new double[graph.N]; // distance to source
    delete[] dist;
*/
    size_t *prev = new size_t[graph.N]; // visited nodes: pointer to previous node or UNEXPLORED

    std::vector<size_t> prio_queue; // priority queue

    for (size_t i = 0; i < graph.N; i++)
    {
        prio_queue.push_back(i);
        dist[i] = INFINITE;
        prev[i] = UNEXPLORED;
    }

    dist[Source] = 0;

    // execution
    while (!prio_queue.empty())
    {
        size_t u = get_closest_node_from_queue(prio_queue, dist, graph.N);

        /*if (u == Target)
            break;
        */

        for (auto neighbor : graph.adjlist[u])
        {
            if (contains(prio_queue, neighbor))
            {
                double tempDist = dist[u] + graph.get_edge_weight(u, neighbor);
                if (tempDist < dist[neighbor])
                {
                    dist[neighbor] = tempDist;
                    prev[neighbor] = u;
                }
            }
        }
    }

    // display

    const int COLWID1 = 10;
    const int COLWID2 = 50;
    const int COLWID3 = 15;

    const std::string GREEN("\033[0;32m");
    const std::string BLUE("\033[0;34m");
    const std::string YELLOW("\033[0;33m");
    const std::string CYAN("\033[0;36m");
    const std::string MAGENTA("\033[0;35m");
    const std::string RESET("\033[0m");

    // header
    std::cout << std::endl
              << "Source: " << Source << " Target: " << Target << std::endl;
    std::cout << "|" << std::setw(COLWID1) << std::left << "  Nodes";
    std::cout << "|" << std::setw(COLWID2) << std::left << "  Shortest Path";
    std::cout << "|" << std::setw(COLWID3) << std::left << "  Distance";
    std::cout << "|" << std::endl;

    std::cout << "|" << std::string(COLWID1, '-');
    std::cout << "|" << std::string(COLWID2, '-');
    std::cout << "|" << std::string(COLWID3, '-');
    std::cout << "|" << std::endl;

    std::list<size_t> path_source_to_target;

    for (int i = 0; i < graph.N; i++)
    {
        std::string format;

        if (i == Target)
            format = GREEN;
        else
            format = RESET;

        std::stringstream ss1;
        ss1 << "  " << Source << " - " << i;

        std::cout << "|" << format << std::setw(COLWID1)
                  << std::left << ss1.str() << RESET << "|" << std::flush;

        std::list<size_t> path;
        size_t k = i;
        if (prev[k] != UNEXPLORED || k == Source)
        {
            while (k != UNEXPLORED)
            {
                path.push_front(k);
                k = prev[k];
            }
        }
        if (i == Target)
            path_source_to_target = path;

        std::stringstream ss2;
        ss2 << "  ";
        for (auto node : path)
        {
            ss2 << node << " -> " << std::flush;
        }
        ss2 << "/";

        std::cout << format << std::setw(COLWID2) << ss2.str() << RESET;
        std::cout << "|  " << format << std::setw(COLWID3 - 2) << dist[i] << RESET << "|" << std::endl;
    }

    // tear down
    delete[] prev;

    return path_source_to_target;
    ;
}

Graph AdjList_from_AdjMatrix(std::vector<std::vector<bool>> Adjacency,
                             std::vector<std::vector<double>> NodeCoordinates)
{

    int N = Adjacency.size(); // number of nodes

    Graph g(N); // create adjacency list

    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            if (Adjacency[i][j])
            {
                double x1 = NodeCoordinates[i][0];
                double y1 = NodeCoordinates[i][1];
                double x2 = NodeCoordinates[j][0];
                double y2 = NodeCoordinates[j][1];
                double distance = sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2));
                g.addedge(i, j, distance, false);
            }
        }
    }

    return g;
}

void print_matrix(std::vector<std::vector<bool>> mat)
{
    for (int i = 0; i < mat.size(); i++)
    {
        for (int j = 0; j < mat[0].size(); j++)
        {
            std::cout << mat[i][j] << " " << std::flush;
        }

        std::cout << std::endl;
    }
    std::cout << std::endl;
}