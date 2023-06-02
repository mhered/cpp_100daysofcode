#include <cmath>
#include <matplot/matplot.h>

void example_3(std::vector<std::vector<double>> &NodeCoordinates,
               std::vector<std::vector<bool>> &Adjacency)
{
    NodeCoordinates = {
        {20.0, 60.0},   // Node 00
        {40.0, 60.0},   // Node 01
        {20.0, 40.0},   // Node 02
        {40.0, 40.0},   // Node 03
        {40.0, 10.0},   // Node 04
        {60.0, 10.0},   // Node 05
        {80.0, 25.0},   // Node 06
        {80.0, 45.0},   // Node 07
        {80.0, 70.0},   // Node 08
        {100.0, 30.0},  // Node 09
        {100.0, 50.0},  // Node 10
        {100.0, 70.0},  // Node 11
        {100.0, 90.0},  // Node 12
        {120.0, 30.0},  // Node 13
        {120.0, 50.0},  // Node 14
        {120.0, 90.0}}; // Node 15

    Adjacency = {
        {1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, // Node 00
        {1, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, // Node 01
        {0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, // Node 02
        {0, 1, 1, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0}, // Node 03
        {0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, // Node 04
        {0, 0, 0, 1, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0}, // Node 05
        {0, 0, 0, 0, 0, 0, 1, 1, 0, 1, 0, 0, 0, 0, 0, 0}, // Node 06
        {0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0}, // Node 07
        {0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0}, // Node 08
        {0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 1, 0, 0}, // Node 09
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 1, 0}, // Node 10
        {0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 1, 0, 0, 0, 0}, // Node 11
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 1}, // Node 12
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 1, 0}, // Node 13
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 1}, // Node 14
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1}, // Node 15
    };
}

void get_coordinates(std::vector<std::vector<double>> NodeCoordinates, std::vector<double> &x, std::vector<double> &y)
{
    for (int i = 0; i < NodeCoordinates.size(); i++)
    {
        x.push_back(NodeCoordinates[i][0]);
        y.push_back(NodeCoordinates[i][1]);
    }
}

void get_edges_and_weights(
    std::vector<std::vector<bool>> Adjacency,
    std::vector<std::pair<size_t, size_t>> &edges,
    std::vector<std::vector<double>> NodeCoordinates,
    std::vector<double> &weights)
{
    for (int i = 0; i < Adjacency.size(); i++)
    {
        for (int j = i; j < Adjacency.size(); j++) // Adjacency assumed symmetrical
        {
            if (Adjacency[i][j])
            {
                edges.push_back({i, j});

                double x1 = NodeCoordinates[i][0];
                double y1 = NodeCoordinates[i][1];
                double x2 = NodeCoordinates[j][0];
                double y2 = NodeCoordinates[j][1];
                double distance = sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2));
                weights.push_back(distance);
            }
        }
    }
}

void FasterPlotGraph(std::vector<std::vector<double>> NodeCoordinates,
                     std::vector<std::vector<bool>> Adjacency)
{

    std::vector<double> x, y;
    get_coordinates(NodeCoordinates, x, y);
    // x: {0, 0.5, -0.5, -0.5, 0.5, 0, 1.5, 0, 2, -1.5, -2}
    // y: {0, 0.5, 0.5, -0.5, -0.5, 2, 0, -2, 0, 0, 0}

    std::vector<std::pair<size_t, size_t>> edges;
    std::vector<double> weights;

    get_edges_and_weights(Adjacency, edges, NodeCoordinates, weights);
    // edges:{{0, 1}, {0, 2}, {0, 3}, {0, 4}, {0, 6}, {0, 9}, {1, 5}, {1, 6}, {2, 5}, {2, 9}, {3, 7}, {3, 9}, {4, 6}, {4, 7}, {5, 8}, {5, 10}, {6, 8}, {7, 8}, {7, 10}, {9, 10}};
    // weights: {1, 1, 1, 1, 3, 3, 2, 4, 1, 6, 2, 8, 8, 9, 3, 2, 10, 12, 15, 16};

    auto g = matplot::graph(edges);
    g->marker("o");
    g->node_color("red");
    g->marker_size(12);
    g->line_style("_");
    g->x_data(x);
    g->y_data(y);

    g->edge_labels(weights);
    matplot::view(2); // top view

    matplot::show();
}
int main()
{

    std::vector<std::vector<double>> NodeCoordinates;
    std::vector<std::vector<bool>> Adjacency;

    example_3(NodeCoordinates, Adjacency); // initialize

    FasterPlotGraph(NodeCoordinates, Adjacency);
    return 0;
}