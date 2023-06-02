#include <iostream>
#include <opencv2/opencv.hpp>
#include "graphutils.h"

std::vector<std::pair<size_t, size_t>> get_neighbors(size_t i, size_t j, cv::Mat map)
{
    int M = map.rows;
    int N = map.cols;

    std::vector<std::pair<size_t, size_t>> neighbors;

    for (int di = -1; di <= 1; di++)
    {
        for (int dj = -1; dj <= 1; dj++)
        {
            if (di == 0 && dj == 0)
                continue;
            int ii = i + di;
            int jj = j + dj;
            if (ii >= 0 && ii < M && jj >= 0 && jj < N && (int)map.at<uchar>(ii, jj) > 200)
                neighbors.push_back({ii, jj});
        }
    }
    return neighbors;
}

std::pair<double, double> get_node_coordinates(size_t i, size_t j, size_t M, double resolution)
{
    double x = j * resolution;
    double y = (M - i - 1) * resolution;
    std::pair<double, double> coords = {x, y};
    return coords;
}

void make_graph(cv::Mat map, std::vector<std::vector<double>> &NodeCoordinates, std::vector<std::vector<bool>> &Adjacency)
{
    size_t M = map.rows;
    size_t N = map.cols;
    double RESOLUTION = 10.0; // ej. cm per pixel

    graph g(M * N);
    for (size_t i = 0; i < M; i++)
    {
        for (size_t j = 0; j < N; j++)
        {
            std::pair<double, double> node_coords = get_node_coordinates(i, j, M, RESOLUTION);
            NodeCoordinates.push_back({node_coords.first, node_coords.second});

            if ((int)map.at<uchar>(i, j) > 200) // free pixel
            {
                std::vector<std::pair<size_t, size_t>> neighbors = get_neighbors(i, j, map);

                for (auto neighbor : neighbors)
                {
                    size_t ii = neighbor.first;
                    size_t jj = neighbor.second;
                    g.addedge(i * N + j, ii * N + jj, false);
                }
            }
        }
    }
    Adjacency = AdjMatrix_from_AdjList(g);
}

int main()
{
    std::string filename = "./assets/map2.bmp"; // "notfound.bmp";
    std::string window_name = "Map";
    cv::Mat image;
    image = cv::imread(filename, cv::IMREAD_GRAYSCALE);

    if (image.empty())
    {
        std::cout << "Could not open or find the image \"" << filename << "\" I'll show you White." << std::endl;
        // create a new image
        // 1 x 8 bits channel
        // 3x 4 resolution (4 wide and 3 high)
        cv::Mat image2(3, 4, CV_8UC1, 255);
        image2.at<uchar>(1, 2) = 0; // 1 black pixel
        image = image2;
        window_name = "Default Map"; // Name of the window
    }

    // create a window
    cv::namedWindow(window_name, cv::WINDOW_NORMAL); // WINDOW_NORMAL can resize, WINDOW_AUTOSIZE cannot
    // show image inside the window
    cv::imshow(window_name, image);

    std::vector<std::vector<double>> NodeCoordinates;
    std::vector<std::vector<bool>> Adjacency;
    make_graph(image, NodeCoordinates, Adjacency);

    graph g = AdjList_from_AdjMatrix(Adjacency);
    g.print();

    PlotGraph(NodeCoordinates, Adjacency);

    // wait for keystroke
    cv::waitKey(0);
    return 0;
}