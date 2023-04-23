#include <cmath>
#include <iostream>
#include <matplot/matplot.h>
#include <set>
#include <thread>
#include <vector>

using namespace matplot;

void Example_plot3D()
{

    auto [X, Y, Z] = peaks();
    surf(X, Y, Z);
    colormap(palette::spring());
    xlim({0, inf});

    show();
    save("plot3D.png");
}

void Example_heatmap()
{

    std::vector<std::vector<double>> data = {
        {45, 60, 32}, {43, 54, 76}, {32, 94, 68}, {23, 95, 58}};
    heatmap(data);
    title("T-Shirt Orders");
    auto ax = gca();
    ax->x_axis().ticklabels({"Small", "Medium", "Large"});
    ax->y_axis().ticklabels({"Green", "Red", "Blue", "Gray"});
    xlabel(ax, "Sizes");
    ylabel(ax, "Colors");

    show();
    save("heatmap.png");
}

void Example_polarhistogram()
{

    std::vector<int> theta = {1, 11, 5, 34, 23, 5, 32, 0, 0, 3, 4, 6, 23, 21, 35, 0, 6, 1, 0, 0};

    auto h = polarhistogram(theta, theta.size());

    h->face_color("red");
    h->face_alpha(1.f - 0.3f);
    show();
    save("polar.png");
}

int main()
{
    Example_heatmap();
    Example_polarhistogram();
    Example_plot3D();

    return 0;
}