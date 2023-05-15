#ifndef BLOB_H
#define BLOB_H

#pragma once
#include <opencv2/opencv.hpp>
#include <vector>

// define colors
const cv::Scalar COLOR_BLACK = cv::Scalar(0.0, 0.0, 0.0);
const cv::Scalar COLOR_WHITE = cv::Scalar(255.0, 255.0, 255.0);

const cv::Scalar COLOR_BLUE = cv::Scalar(255.0, 144.0, 30.0);
const cv::Scalar COLOR_GREEN = cv::Scalar(127.0, 255.0, 0.0);
const cv::Scalar COLOR_DARK_GREEN = cv::Scalar(34.0, 139.0, 34.0);
const cv::Scalar COLOR_RED = cv::Scalar(0.0, 0.0, 255.0);
const cv::Scalar COLOR_YELLOW = cv::Scalar(51.0, 250.0, 255.0);
const cv::Scalar COLOR_CYAN = cv::Scalar(255.0, 255.0, 0.0);
const cv::Scalar COLOR_ORANGE = cv::Scalar(80.0, 127.0, 255.0);
const cv::Scalar COLOR_PINK = cv::Scalar(180.0, 105.0, 255.0);
const cv::Scalar COLOR_VIOLET = cv::Scalar(238.0, 130.0, 238.0);
const cv::Scalar COLOR_BROWN = cv::Scalar(30.0, 105.0, 210.0);

class Blob
{
    static std::vector<cv::Scalar> COLORS;
    static int count;
    static int last_color;

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

    cv::Scalar color;
};

#endif