#ifndef BLOB_H
#define BLOB_H

#pragma once
#include <opencv2/opencv.hpp>

class Blob
{
public:
    std::vector<cv::Point> contour;
    cv::Rect rect;

    double diagonal;
    double aspect_ratio;

    Blob(std::vector<cv::Point> _contour);

    std::vector<cv::Point> positions;
    bool match_or_new;
    bool being_tracked;
    int frames_without_match;
    cv::Point predicted_next_pos;
    void predict_next_pos(void);
};

#endif