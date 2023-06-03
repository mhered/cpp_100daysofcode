#ifndef GRAPH_H
#define GRAPH_H

#pragma once
#include <iostream> // list
#include <list>     // cout

class Graph
{
public:
    std::list<size_t> *adjlist; // adjacency list
    size_t N; // number of nodes in the graph
    double *weights; // adjacency matrix with edge weights
    Graph(size_t n); // constructor
    ~Graph();

    void addedge(size_t u, size_t v, double weight, bool bi);
    double get_edge_weight(size_t u, size_t v);
    void print();

private:
};

#endif