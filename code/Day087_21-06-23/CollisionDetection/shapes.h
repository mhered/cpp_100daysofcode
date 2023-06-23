#ifndef SHAPES_H
#define SHAPES_H

#pragma once

#include <opencv2/opencv.hpp>

////////Segment////////////
///////////////////////////

class Segment
{
    static constexpr double TOL = 0.1f;

public:
    double x1;
    double y1;
    double x2;
    double y2;
    Segment(double x1, double y1,
            double x2, double y2) : x1(x1), y1(y1),
                                    x2(x2), y2(y2){};
    Segment(cv::Point2d pt1, cv::Point2d pt2) : x1(pt1.x), y1(pt1.y),
                                                x2(pt2.x), y2(pt2.y){};
    bool is_pt_on_segment(double x, double y);
    void draw(cv::Mat &img, cv::Scalar color);
};


////////Circle/////////////
///////////////////////////

class Circle
{
    static constexpr double TOL = 0.1f;

public:
    double centre_x;
    double centre_y;
    double radius;
    bool collides_with(Circle other);
    bool collides_with(Segment other);
    void draw(cv::Mat &img, cv::Scalar color);
    Circle(double centre_x,
           double centre_y,
           double radius) : centre_x(centre_x),
                            centre_y(centre_y),
                            radius(radius){};
};

////////Rectangle//////////
///////////////////////////

class Rectangle
{
    static constexpr double TOL = 0.1f;

public:
    double centre_x;
    double centre_y;
    double width;
    double height;
    double angle_deg;

    Rectangle(double centre_x,
              double centre_y,
              double angle_deg,
              double width,
              double height) : centre_x(centre_x),
                               centre_y(centre_y),
                               width(width),
                               height(height),
                               angle_deg(angle_deg){};

    std::vector<cv::Point> vertices();
    void draw(cv::Mat &img, cv::Scalar color);
    bool collides_with(Circle other);
    bool collides_with(Rectangle other);

private:
    // primitive
    std::vector<cv::Point2d> primitive = {
        {-width / 2.0, -height / 2.0},
        {width / 2.0, -height / 2.0},
        {width / 2.0, height / 2.0},
        {-width / 2.0, height / 2.0}}; // double type
};


#endif