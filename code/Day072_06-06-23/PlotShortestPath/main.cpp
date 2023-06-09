#include <cmath>
#include <matplot/matplot.h>
#include "dijkstra.hpp"
#include "examples.h"

void get_coordinates(std::vector<std::vector<double>> NodeCoordinates,
                     std::vector<double> &x,
                     std::vector<double> &y)
{
    for (int i = 0; i < NodeCoordinates.size(); i++)
    {
        x.push_back(NodeCoordinates[i][0]);
        y.push_back(NodeCoordinates[i][1]);
    }
}

void get_edges_and_weights(
    Graph &g,
    std::vector<std::pair<size_t, size_t>> &edges,
    std::vector<std::vector<double>> NodeCoordinates,
    std::vector<double> &weights)
{

    std::vector<std::vector<bool>> Adjacency;
    Adjacency = g.adjmatrix(); // there is a better way to scan edges in a Graph!!

    for (int i = 0; i < Adjacency.size(); i++)
    {
        for (int j = 0; j < Adjacency.size(); j++)
        {
            if (Adjacency[i][j]) // does not assume Adjacency symmetrical
            {
                edges.push_back({i, j});

                /*double x1 = NodeCoordinates[i][0];
                double y1 = NodeCoordinates[i][1];
                double x2 = NodeCoordinates[j][0];
                double y2 = NodeCoordinates[j][1];
                double edge_length = sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2));
                edge_lengths.push_back(edge_length);*/
                weights.push_back(g.get_edge_weight(i, j));
            }
        }
    }
}

void PlotDijkstra(Graph &g,
                  std::vector<std::vector<double>> NodeCoordinates,
                  std::vector<double> dist,
                  std::list<size_t> path)
{

    std::vector<double> x, y;
    get_coordinates(NodeCoordinates, x, y);

    std::vector<std::pair<size_t, size_t>> edges;
    std::vector<double> weights;

    get_edges_and_weights(g, edges, NodeCoordinates, weights);

    /*// simulated distance to Source
    std::vector<double> dist;
    for (int i = 0; i < NodeCoordinates.size(); i++)
    {
        dist.push_back(10.0 * i / (double)NodeCoordinates.size());
    }*/

    // highlight shortest path
    // this approach wont work!!
    // need to scan path, identify pairs of nodes u,v, find the edge and make the K = 1.0
    std::vector<double> thickness;
    // initialize thicknesses to thin
    for (size_t k = 0; k < edges.size(); k++)
    {
        thickness.push_back(0.);
    }

    std::vector<size_t> path_as_vector{std::begin(path), std::end(path)};

    size_t v;
    // PENDING deal with path.size()<2!!
    for (size_t i = 0; i < path_as_vector.size() - 1; i++) // if edge found in path display it thicker
    {
        size_t u, v;
        u = path_as_vector[i];
        v = path_as_vector[i + 1];

        // find edge in path
        for (size_t k = 0; k < edges.size(); k++)
        {
            size_t i = edges[k].first;
            size_t j = edges[k].second;
            if (i == u && j == v) // edge in path found
            {
                thickness[k] = 1.0;
                break;
            }
        }
    }

    auto graph = matplot::graph(edges);
    graph->is_2d();
    graph->marker("o");
    // graph->node_color("red");
    graph->marker_size(12);
    graph->line_style("_");
    graph->x_data(x);
    graph->y_data(y);

    graph->edge_labels(weights);

    // colorize nodes by distance to source
    matplot::colormap(matplot::palette::autumn(10));
    matplot::colorbar();
    graph->marker_colors(dist);

    // graph->line_width(3);
    graph->line_style("g");
    // highlight shortest path
    graph->line_widths(thickness); // buggy, only works in undirected graphs, but not in vertical edges...

    matplot::view(2); // top view

    matplot::show();
}

int main()
{
    // create graph by adding edges
    /*
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

    std::vector<std::vector<double>> NodeCoordinates;
    NodeCoordinates = {
        // Adjacency matrix can be inferred but need additional info on NodeCoordinates
        {10.0, 20.0}, // Node 00
        {28.0, 30.0}, // Node 01
        {32.0, 10.0}, // Node 02
        {48.0, 30.0}, // Node 03
        {52.0, 10.0}  // Node 04
    };

    */

    // or using the 3 graph examples from previous days

    std::vector<std::vector<double>> NodeCoordinates;
    std::vector<std::vector<bool>> Adjacency;

    // example_1(NodeCoordinates, Adjacency);
    // example_2(NodeCoordinates, Adjacency);
    example_3(NodeCoordinates, Adjacency);

    print_matrix(Adjacency);
    Graph g = AdjList_from_AdjMatrix(Adjacency, NodeCoordinates);

    g.print();

    double *dist = new double[g.N]; // distance to source
    std::list<size_t> path;
    // path = dijkstra(g, 0, 2, dist);

    // shortest path from 0 to 3 and latest calculated values of all node distances to 3 (note algorithm stops when 3 is reached)
    path = dijkstra(g, 10, 2, dist);

    // get dist in proper format
    std::vector<double> dist_as_vector;
    for (int i = 0; i < g.N; i++)
    {
        dist_as_vector.push_back(dist[i]);
    }

    PlotDijkstra(g, NodeCoordinates, dist_as_vector, path);

    delete[] dist;

    return 0;
}
