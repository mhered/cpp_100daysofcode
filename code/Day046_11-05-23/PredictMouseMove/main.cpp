
#include <opencv2/opencv.hpp>
#include <iostream>

// define colors
const cv::Scalar COLOR_WHITE = cv::Scalar(255.0, 255.0, 255.0);
const cv::Scalar COLOR_BLACK = cv::Scalar(0.0, 0.0, 0.0);
const cv::Scalar COLOR_BLUE = cv::Scalar(255.0, 0.0, 0.0);
const cv::Scalar COLOR_GREEN = cv::Scalar(0.0, 200.0, 0.0);
const cv::Scalar COLOR_RED = cv::Scalar(0.0, 0.0, 255.0);
const cv::Scalar COLOR_GRAY = cv::Scalar(128.0, 128.0, 128.0);

cv::Point mouse_pos(0, 0);

cv::Point predict_next_mouse_pos(std::vector<cv::Point> &positions)
{
    cv::Point next_pos;

    int n = positions.size();

    if (n == 0)
    {
        std::cerr << "ERROR - predict_next_mouse_pos was called with zero points\n";
    }
    else if (n == 1)
    {
        return positions[0];
    }
    else if (n == 2)
    {

        int sumOfXChanges = ((positions[n - 1].x - positions[n - 2].x) * 1);

        int sumOfYChanges = ((positions[n - 1].y - positions[n - 2].y) * 1);

        int deltaX = (int)std::round((float)sumOfXChanges);
        int deltaY = (int)std::round((float)sumOfYChanges);

        next_pos.x = positions.back().x + deltaX;
        next_pos.y = positions.back().y + deltaY;
    }
    else if (n >= 3)
    {

        int sumOfXChanges = ((positions[n - 1].x - positions[n - 2].x) * 2) +
                            ((positions[n - 2].x - positions[n - 3].x) * 1);

        int sumOfYChanges = ((positions[n - 1].y - positions[n - 2].y) * 2) +
                            ((positions[n - 2].y - positions[n - 3].y) * 1);

        int deltaX = (int)std::round((float)sumOfXChanges / 3.0);
        int deltaY = (int)std::round((float)sumOfYChanges / 3.0);

        next_pos.x = positions.back().x + deltaX;
        next_pos.y = positions.back().y + deltaY;
    }
    /*
    // no need to include so many points in the prediction
    else if (n == 4)
    {

        int sumOfXChanges = ((positions[n - 1].x - positions[n - 2].x) * 3) +
                            ((positions[n - 2].x - positions[n - 3].x) * 2) +
                            ((positions[n - 3].x - positions[n - 4].x) * 1);

        int sumOfYChanges = ((positions[n - 1].y - positions[n - 2].y) * 3) +
                            ((positions[n - 2].y - positions[n - 3].y) * 2) +
                            ((positions[n - 3].y - positions[n - 4].y) * 1);

        int deltaX = (int)std::round((float)sumOfXChanges / 6.0);
        int deltaY = (int)std::round((float)sumOfYChanges / 6.0);

        next_pos.x = positions.back().x + deltaX;
        next_pos.y = positions.back().y + deltaY;
    }
    else if (n >= 5)
    {

        int sumOfXChanges = ((positions[n - 1].x - positions[n - 2].x) * 4) +
                            ((positions[n - 2].x - positions[n - 3].x) * 3) +
                            ((positions[n - 3].x - positions[n - 4].x) * 2) +
                            ((positions[n - 4].x - positions[n - 5].x) * 1);

        int sumOfYChanges = ((positions[n - 1].y - positions[n - 2].y) * 4) +
                            ((positions[n - 2].y - positions[n - 3].y) * 3) +
                            ((positions[n - 3].y - positions[n - 4].y) * 2) +
                            ((positions[n - 4].y - positions[n - 5].y) * 1);

        int deltaX = (int)std::round((float)sumOfXChanges / 10.0);
        int deltaY = (int)std::round((float)sumOfYChanges / 10.0);

        next_pos.x = positions.back().x + deltaX;
        next_pos.y = positions.back().y + deltaY;
    }
    */

    return next_pos;
}

void mouseMoveCallback(int event, int x, int y, int flags, void *userData)
{
    // store mouse position in global variable

    if (event == cv::EVENT_MOUSEMOVE)
    {
        mouse_pos.x = x;
        mouse_pos.y = y;
    }
}

void drawCross(cv::Mat &img, cv::Point pt, cv::Scalar color)
{
    // draw a small cross of given color at given pt
    cv::line(img, cv::Point(pt.x - 5, pt.y - 5), cv::Point(pt.x + 5, pt.y + 5), color, 2);
    cv::line(img, cv::Point(pt.x + 5, pt.y - 5), cv::Point(pt.x - 5, pt.y + 5), color, 2);
}

int main(void)
{
    // declare a blank image for moving the mouse over
    cv::Mat canvas(800, 1200, CV_8UC3, cv::Scalar::all(0));

    std::vector<cv::Point> positions;

    cv::Point next_pos;

    // declare window
    std::string windowname = "canvas | ESC to close";
    cv::namedWindow(windowname);
    cv::setMouseCallback(windowname, mouseMoveCallback);

    const int ESC_KEY = 27;

    while (true)
    {

        // clear the canvas
        canvas = cv::Scalar::all(0);

        // get the current position
        positions.push_back(mouse_pos);

        // predict the next position
        next_pos = predict_next_mouse_pos(positions);

        std::cout << "current position   = " << positions.back().x << ", " << positions.back().y << "\n";
        std::cout << "predicted position = " << next_pos.x << ", " << next_pos.y << "\n";
        std::cout << "------------------------------\n";

        // draw a blue cross at the next predicted mouse position
        drawCross(canvas, next_pos, COLOR_GREEN);
        // draw a white cross at current mouse position
        drawCross(canvas, positions.back(), COLOR_WHITE);

        // show the image
        cv::imshow(windowname, canvas);

        // check for ESC / pause to redraw the canvas
        if (cv::waitKey(10) == ESC_KEY)
            break;
    }

    return 0;
}
