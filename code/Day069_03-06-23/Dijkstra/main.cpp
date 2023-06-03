#include <iostream>
#include <vector>
#include "Graph.h"
#include <algorithm>
#include <sstream>
#include <iomanip>
#include <cmath>
#include "examples.h"

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

void dijkstra(Graph &graph, size_t Source, size_t Target)
{
    // initialization
    const double INFINITE = MAXFLOAT;
    const size_t UNEXPLORED = graph.N;

    double *dist = new double[graph.N]; // distance to source
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

        if (u == Target)
            break;

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
    const int COLWID2 = 48;
    const int COLWID3 = 12;
    // header
    std::cout << "|" << std::setw(COLWID1) << std::left << "  Nodes";
    std::cout << "|" << std::setw(COLWID2) << std::left << "  Shortest Path";
    std::cout << "|" << std::setw(COLWID3) << std::left << "  Distance";
    std::cout << "|" << std::endl;

    std::cout << "|" << std::string(COLWID1, '-');
    std::cout << "|" << std::string(COLWID2, '-');
    std::cout << "|" << std::string(COLWID3, '-');
    std::cout << "|" << std::endl;

    for (int i = 0; i < graph.N; i++)
    {
        std::stringstream ss1;
        ss1 << "  " << Source << " - " << i;

        std::cout << "|" << std::setw(COLWID1)
                  << std::left << ss1.str() << "|" << std::flush;

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
        std::stringstream ss2;
        ss2 << "  ";
        for (auto node : path)
        {
            ss2 << node << " -> " << std::flush;
        }
        ss2 << "/";

        std::cout << std::setw(COLWID2) << ss2.str();
        std::cout << "|  " << std::setw(COLWID3 - 2) << dist[i] << "|" << std::endl;
    }

    // tear down
    delete[] dist;
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

int main()
{
    // create graph by adding edges

    Graph g(5);

    g.addedge(0, 1, 10.0, false);
    g.addedge(0, 2, 3.0, false);
    g.addedge(1, 2, 1.0, false);
    g.addedge(1, 3, 2.0, false);
    g.addedge(2, 1, 4.0, false);
    g.addedge(2, 3, 8.0, false);
    g.addedge(2, 4, 2.0, false);
    g.addedge(3, 4, 7.0, false);
    g.addedge(4, 3, 9.0, false);

    // or using the 3 graph examples from previous days

    /*std::vector<std::vector<double>> NodeCoordinates;
    std::vector<std::vector<bool>> Adjacency;

    // example_1(NodeCoordinates, Adjacency);
    // example_2(NodeCoordinates, Adjacency);
    // example_2(NodeCoordinates, Adjacency);

    PlotGraph(NodeCoordinates, Adjacency);
    print_matrix(Adjacency);
    Graph g = AdjList_from_AdjMatrix(Adjacency, NodeCoordinates);
    */

    g.print();

    dijkstra(g, 0, 2);

    return 0;
}