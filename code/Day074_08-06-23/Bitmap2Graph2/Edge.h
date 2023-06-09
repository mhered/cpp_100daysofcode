#ifndef EDGE_H
#define EDGE_H

#pragma once

#include "Node.h"

class Edge
{
public:
    Edge(Node pt_node_1, Node pt_node_2) : pt_node_1(pt_node_1),
                                           pt_node_2(pt_node_2)
    {
        compute_distance();
    };
    Edge();
    ~Edge();

    double distance;
    Node pt_node_1;
    Node pt_node_2;
    void compute_distance();
};

#endif