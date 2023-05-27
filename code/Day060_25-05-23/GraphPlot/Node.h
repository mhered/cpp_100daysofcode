#ifndef NODE_H
#define NODE_H

#pragma once

class Node
{

public:
    Node(double x, double y) : id(++count), x(x), y(y){};
    Node();
    ~Node();
    static long const MAX_NUM_NODES = 50;
    double get_x() { return x; };
    double get_y() { return y; };

    static long count;
    long id;
    double x;
    double y;
};

#endif