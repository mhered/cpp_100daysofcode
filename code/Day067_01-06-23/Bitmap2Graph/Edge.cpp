#include "Edge.h"
#include <cmath>
Edge::Edge()
{
}

Edge::~Edge()
{
}

void Edge::compute_distance()
{
    double x1 = pt_node_1.get_x();
    double y1 = pt_node_1.get_y();
    double x2 = pt_node_2.get_x();
    double y2 = pt_node_2.get_y();
    distance = sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2));
}