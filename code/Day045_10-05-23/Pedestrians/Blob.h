#ifndef BLOB_H
#define BLOB_H

#pragma once
#include <opencv2/opencv.hpp>

class Blob
{
public:
    std::vector<cv::Point> contour;
    cv::Rect rect;
    cv::Point centre;

    double diagonal;
    double aspect_ratio;

    Blob(std::vector<cv::Point> _contour);
};

#endif