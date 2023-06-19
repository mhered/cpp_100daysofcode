#include <opencv2/opencv.hpp>
#include "kbhit.h"
#include <iostream>

const cv::Scalar COLOR_BLUE = cv::Scalar(255.0, 144.0, 30.0);

const int MOVE_UP = 113;     // q
const int MOVE_DOWN = 97;    // a
const int MOVE_LEFT = 111;   // o
const int MOVE_RIGHT = 112;  // p
const int TURN_CCWISE = 110; // n
const int TURN_CWISE = 109;  // m

const double TSTEP = 5; // translation step
const double RSTEP = 5; // rotation step

const double XMIN = 0;    // x lower bound
const double XMAX = 1100; // x higher bound
const double YMIN = 0;    // y lower bound
const double YMAX = 600;  // y higher bound

const double RECT_HEIGHT = 120;
const double RECT_WIDTH = 220;

// define primitive
std::vector<cv::Point2d> PRIMITIVE = {
    {-RECT_WIDTH / 2.0, -RECT_HEIGHT / 2.0},
    {RECT_WIDTH / 2.0, -RECT_HEIGHT / 2.0},
    {RECT_WIDTH / 2.0, RECT_HEIGHT / 2.0},
    {-RECT_WIDTH / 2.0, RECT_HEIGHT / 2.0}}; // double type

void move_body(double &x, double &y, double &angle)
{
    double x_0 = x;
    double y_0 = y;
    double angle_0 = angle;

    int keypress = cv::waitKey(33) & 255;

    if (keypress == MOVE_UP && y > YMIN + TSTEP)
        y -= TSTEP; // move up TSTEP cm
    else if (keypress == MOVE_DOWN && y < YMAX - TSTEP)
        y += TSTEP; // move down TSTEP cm
    if (keypress == MOVE_RIGHT && x < XMAX - TSTEP)
        x += TSTEP; // move left TSTEP cm
    else if (keypress == MOVE_LEFT && x > XMIN + TSTEP)
        x -= TSTEP; // move right TSTEP cm
    if (keypress == TURN_CCWISE)
        angle -= RSTEP; // rotate counter-clockwise RSTEP degrees
    else if (keypress == TURN_CWISE)
        angle += RSTEP; // rotate clockwise RSTEP degrees

    angle = std::fmod(angle, 360);

    if (x != x_0 || y != y_0 || angle != angle_0)
        std::cout << "x = " << x << " | y= " << y << " | angle = " << angle << std::endl;
}

void loop()
{
    std::cout << "q - move up" << std::endl;
    std::cout << "a - move down" << std::endl;
    std::cout << "o - move left" << std::endl;
    std::cout << "p - move right" << std::endl;
    std::cout << "n - rotate counter-clockwise" << std::endl;
    std::cout << "m - rotate clockwise" << std::endl;

    cv::Mat blank(cv::Size(XMAX, YMAX), CV_8UC3, cv::Scalar(255.0, 255.0, 255.0));
    cv::imshow("Put this window in focus for commands to work", blank);

    // initialize rectangle
    double x_centre = (XMAX - XMIN) / 2;
    double y_centre = (YMAX - YMIN) / 2;
    double angle_deg = 0.0;

    while (true)
    {
        move_body(x_centre, y_centre, angle_deg);

        std::vector<cv::Point> Body;

        // rotate by angle (deg) and then translate to x_centre, y_centre
        double angle_rad = CV_PI / 180 * angle_deg;
        for (int i = 0; i < PRIMITIVE.size(); i++)
        {
            double xx, yy;
            xx = PRIMITIVE[i].x * cos(angle_rad) - PRIMITIVE[i].y * sin(angle_rad);
            yy = PRIMITIVE[i].x * sin(angle_rad) + PRIMITIVE[i].y * cos(angle_rad);
            Body.push_back({(int)(xx + x_centre), (int)(yy + y_centre)});
        }

        // draw body
        cv::Mat frame = blank.clone();
        cv::polylines(frame, Body, true, COLOR_BLUE, 2);
        cv::imshow("Put this window in focus for commands to work", frame);
    }
};

int main()
{
    loop();
}
