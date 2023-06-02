#include <iostream>
#include <list>
#include <vector>

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

    /*
        ~graph()
        {
            delete[] adjlist;
        }
    */
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
    // initialize list of node coordinates and adjacency matrices

    std::vector<std::vector<double>> NodeCoordinates;
    std::vector<std::vector<bool>> Adjacency;

    // example_1(NodeCoordinates, Adjacency);
    // example_2(NodeCoordinates, Adjacency);

    example_3(NodeCoordinates, Adjacency);

    // PlotGraph(NodeCoordinates, Adjacency);

    print_matrix(Adjacency);

    graph g = AdjList_from_AdjMatrix(Adjacency);

    g.print();

    std::vector<std::vector<bool>> AdjMatrix = AdjMatrix_from_AdjList(g);

    print_matrix(AdjMatrix);

    graph g2 = AdjList_from_AdjMatrix(AdjMatrix);
    g2.print();

    return 0;
}
