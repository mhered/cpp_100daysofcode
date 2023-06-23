#include <iostream>
#include <opencv2/opencv.hpp>
#include "shapes.h"

// define colors
const cv::Scalar COLOR_WHITE = cv::Scalar(255.0, 255.0, 255.0);
const cv::Scalar COLOR_BLACK = cv::Scalar(0.0, 0.0, 0.0);
const cv::Scalar COLOR_BLUE = cv::Scalar(255.0, 0.0, 0.0);
const cv::Scalar COLOR_GREEN = cv::Scalar(0.0, 200.0, 0.0);
const cv::Scalar COLOR_RED = cv::Scalar(0.0, 0.0, 255.0);
const cv::Scalar COLOR_GRAY = cv::Scalar(128.0, 128.0, 128.0);

// define initial state
int WIDTH = 1100;
int HEIGHT = 600;

// Parameters for target
double x_0 = (double)(WIDTH / 2);
double y_0 = (double)(HEIGHT / 2);
double RADIUS_0 = 120;

bool ROTATECCW_FLAG = false;
bool ROTATECW_FLAG = false;
// initialize user_shape as global variable to receive MouseCallback

// testing Circle
/*double RADIUS1 = 30;
Circle user_shape(0, 0, RADIUS1);*/

// testing Rectangle
double RECT_HEIGHT = 260;
double RECT_WIDTH = 80;
Rectangle user_shape(0.0, 0.0, -30.0, RECT_WIDTH, RECT_HEIGHT);

// testing Segment
// requires changes to mouseMoveCallback
// Segment user_shape(0, 0, WIDTH, HEIGHT);

void mouseMoveCallback(int event, int x, int y, int flags, void *userData)
{
    // store mouse position in a global variable
    if (event == cv::EVENT_MOUSEMOVE)
    {
        user_shape.centre_x = x;
        user_shape.centre_y = y;
    }

    if (event == cv::EVENT_LBUTTONDOWN)
    {
        ROTATECCW_FLAG = true;
    }
    else if (event == cv::EVENT_LBUTTONUP)
    {
        ROTATECCW_FLAG = false;
    }

    if (event == cv::EVENT_RBUTTONDOWN)
    {
        ROTATECW_FLAG = true;
    }
    else if (event == cv::EVENT_RBUTTONUP)
    {
        ROTATECW_FLAG = false;
    }

    if (ROTATECCW_FLAG)
        user_shape.angle_deg += 1;
    if (ROTATECW_FLAG)
        user_shape.angle_deg -= 1;
}

int main(void)
{
    // declare a blank canvas
    cv::Mat canvas(HEIGHT, WIDTH, CV_8UC3, cv::Scalar::all(255));

    // declare window
    std::string windowname = "canvas | ESC to close";
    cv::namedWindow(windowname);

    // set mouse callback
    cv::setMouseCallback(windowname, mouseMoveCallback);

    const int ESC_KEY = 27;

    // declare target
    Circle target(x_0, y_0, RADIUS_0);

    while (true)
    {
        // clear the canvas
        canvas = cv::Scalar::all(255);

        cv::Scalar color = user_shape.collides_with(target) ? COLOR_RED : COLOR_GREEN;

        // draw circle
        user_shape.draw(canvas, color);
        // draw target circle
        target.draw(canvas, COLOR_GRAY);

        // show the image
        cv::imshow(windowname, canvas);

        // check for ESC / pause to redraw the canvas
        if (cv::waitKey(10) == ESC_KEY)
            break;
    }

    return 0;
}
