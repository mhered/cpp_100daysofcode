#include "Graph.h"

Graph::Graph(size_t n) // constructor
{
    std::cout << "Creating Graph" << std::endl;

    adjlist = new std::list<size_t>[n];
    weights = new double[n * n];
    N = n;
}

Graph::~Graph()
{
    std::cout << "Deleting Graph" << std::endl;
    delete[] adjlist;
    delete[] weights;
}

void Graph::addedge(size_t u, size_t v, double weight = 0, bool bi = false)
{
    adjlist[u].push_back(v);
    weights[u * N + v] = weight;
    if (bi) // bool bi = true for bidirectional
    {
        adjlist[v].push_back(u);
        weights[v * N + u] = weight;
    }
}

void Graph::print() // print adjacency list
{
    for (size_t u = 0; u < N; u++)
    {
        std::cout << u << " -> ";
        for (auto v : adjlist[u])
        {
            std::cout << v << " (" << weights[u * N + v] << ") ";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

double Graph::get_edge_weight(size_t u, size_t v)
{
    return weights[u * N + v];
}