#include <iostream>
#include "Node.h"
#include "Edge.h"
#include <vector>
#include <sstream>
#include <iomanip>
#include <matplot/matplot.h>

void PlotGraph(std::vector<std::vector<double>> NodeCoordinates,
               std::vector<std::vector<bool>> Adjacency)
{
    int N = NodeCoordinates.size();

    Node *pt_node = new Node[N];

    for (int i = 0; i < N; i++)
    {
        pt_node[i] = Node(NodeCoordinates[i][0], NodeCoordinates[i][1]);
    }

    std::vector<Edge> edges;

    for (int i = 0; i < Adjacency.size(); i++)
    {
        for (int j = 0; j < Adjacency[0].size(); j++)
        {
            if (Adjacency[i][j] && i != j)
            {
                Edge edge(pt_node[i], pt_node[j]);
                edges.push_back(edge);
            }
        }
    }

    std::vector<double> Nx, Ny, Nx_txt;
    std::vector<int> Nid;
    std::vector<std::string> N_name;

    const int FONT_SIZE = 20;
    const double FACTOR = 0.01; // to centre Node ids in circles
    double PARTS = 3;           // to leave gap in edges & arrows

    for (int i = 0; i < N; i++)
    {
        int id = (int)pt_node[i].id - 1;
        Nid.push_back(id);
        N_name.push_back(std::to_string(id));
        Nx.push_back(pt_node[i].x);
        double offset = std::to_string(id).length() * FONT_SIZE * FACTOR;
        Nx_txt.push_back(pt_node[i].x - offset); // offset approx compensates width of text
        Ny.push_back(pt_node[i].y);
    }

    std::vector<double> Ex1, Ey1, Ex2, Ey2;
    for (int i = 0; i < edges.size(); i++)
    {
        Ex1.push_back(edges[i].pt_node_1.x);
        Ey1.push_back(edges[i].pt_node_1.y);
        Ex2.push_back(edges[i].pt_node_2.x);
        Ey2.push_back(edges[i].pt_node_2.y);
    }

    auto nodes = matplot::scatter(Nx, Ny);
    nodes->line_width(4)
        .marker_size(50)
        .marker_color("red")
        .marker_face_color("red");

    // adjust limits

    double MARGIN = 0.2;

    auto x_lims = std::minmax_element(Nx.begin(), Nx.end());
    auto y_lims = std::minmax_element(Ny.begin(), Ny.end());

    double XMIN = *x_lims.first;
    double XMAX = *x_lims.second;
    double YMIN = *y_lims.first;
    double YMAX = *y_lims.second;

    XMIN = XMIN - MARGIN * (XMAX - XMIN);
    XMAX = XMAX + MARGIN * (XMAX - XMIN);
    YMIN = YMIN - MARGIN * (YMAX - YMIN);
    YMAX = YMAX + MARGIN * (YMAX - YMIN);

    matplot::xrange({XMIN, XMAX});
    matplot::yrange({YMIN, YMAX});

    // matplot::axis("equal"); // does not work

    auto node_text = matplot::text(Nx_txt, Ny, N_name);
    node_text->font_size(FONT_SIZE)
        .color("w");
    for (int i = 0; i < edges.size(); i++)
    {

        double x_label = (Ex1[i] + Ex2[i]) / 2;
        double y_label = (Ey1[i] + Ey2[i]) / 2;

        std::stringstream ss;
        ss << std::setprecision(2) << std::fixed << edges[i].distance;
        std::string label = ss.str();

        matplot::text(x_label, y_label, label);

        double dx_arrow = (Ex2[i] - x_label) / PARTS;
        double dy_arrow = (Ey2[i] - y_label) / PARTS;

        auto arrow = matplot::arrow(x_label + dx_arrow,
                                    y_label + dy_arrow,
                                    x_label + (PARTS - 1) * dx_arrow,
                                    y_label + (PARTS - 1) * dy_arrow);
        arrow->line_width(3).color("black");

        auto tail = matplot::line(x_label - (PARTS - 1) * dx_arrow,
                                  y_label - (PARTS - 1) * dy_arrow,
                                  x_label - dx_arrow,
                                  y_label - dy_arrow);
        tail->line_width(1).color("gray");
    }

    matplot::show();

    delete[] pt_node;
}

void example_1(std::vector<std::vector<double>> &NodeCoordinates,
               std::vector<std::vector<bool>> &Adjacency)
{
    NodeCoordinates = {
        {15.0, 8.6603}, // Node 0
        {0.0, 0.0},     // Node 1
        {20.0, 0.0},    // Node 2
        {25.0, 8.6603}, // Node 3
        {10.0, 0.0},    // Node 4
        {5.0, 8.6603}}; // Node 5

    Adjacency = {
        {0, 0, 1, 1, 1, 1},  // Node 0
        {0, 0, 0, 0, 1, 1},  // Node 1
        {0, 0, 0, 1, 1, 0},  // Node 2
        {0, 0, 0, 0, 0, 0},  // Node 3
        {0, 0, 0, 0, 0, 1},  // Node 4
        {1, 0, 0, 0, 0, 0}}; // Node 5
}

void example_2(std::vector<std::vector<double>> &NodeCoordinates,
               std::vector<std::vector<bool>> &Adjacency)
{
    NodeCoordinates = {
        {10.0, 30.0}, // Node 0
        {10.0, 10.0}, // Node 1
        {30.0, 10.0}, // Node 2
        {30.0, 30.0}, // Node 3
        {40.0, 20.0}, // Node 4
    };

    Adjacency = {
        {1, 1, 0, 1, 0},  // Node 0
        {1, 1, 1, 1, 0},  // Node 1
        {0, 1, 1, 1, 1},  // Node 2
        {1, 1, 1, 1, 1},  // Node 3
        {0, 0, 1, 1, 1}}; // Node 4
}

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

int main()
{
    std::vector<std::vector<double>> NodeCoordinates;
    std::vector<std::vector<bool>> Adjacency;

    // example_1(NodeCoordinates, Adjacency); // initialize
    // example_2(NodeCoordinates, Adjacency); // initialize

    example_3(NodeCoordinates, Adjacency); // initialize 

    PlotGraph(NodeCoordinates, Adjacency);

    return 0;
}