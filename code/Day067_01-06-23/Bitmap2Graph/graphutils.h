#include <iostream>
#include <list>
#include <vector>

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

class graph
{
public:
    std::list<int> *adjlist;
    int n;

    graph(int v)
    {
        adjlist = new std::list<int>[v];
        n = v;
    }

    void addedge(int u, int v, bool bi) // bool bi = true for bidirectional
    {
        adjlist[u].push_back(v);
        if (bi)
        {
            adjlist[v].push_back(u);
        }
    }

    void print()
    {
        for (int i = 0; i < n; i++)
        {
            std::cout << i << " -> ";
            for (auto it : adjlist[i])
            {
                std::cout << it << " ";
            }
            std::cout << std::endl;
        }
        std::cout << std::endl;
    }
};

std::vector<std::vector<bool>> AdjMatrix_from_AdjList(graph g)
{
    int N = g.n; // number of nodes in graph
    std::vector<std::vector<bool>> AdjMatrix(N, std::vector<bool>(N, false));
    std::list<int> *lst = g.adjlist;
    for (int i = 0; i < N; i++)
    {
        for (auto it : g.adjlist[i]) // traverse a list
        {
            int j = it;
            AdjMatrix[i][j] = true;
        }
    }
    return AdjMatrix;
}

graph AdjList_from_AdjMatrix(std::vector<std::vector<bool>> Adjacency)
{

    int N = Adjacency.size(); // number of nodes

    graph g(N); // create adjacency list

    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            if (Adjacency[i][j] != 0)
                g.addedge(i, j, false);
        }
    }

    return g;
}
