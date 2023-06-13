#ifndef DOBBLE_H
#define DOBBLE_H

#pragma once

#include <iostream>
#include "opencv2/opencv.hpp"
#include <random>
#include <algorithm>
#include <chrono>

/**
 * @brief Draws a transparent image over a frame Mat.
 *
 * @param frame the frame where the transparent image will be drawn
 * @param transp the Mat image with transparency, read from a PNG image, with the IMREAD_UNCHANGED flag
 * @param xPos x position of the frame image where the image will start.
 * @param yPos y position of the frame image where the image will start.
 */
void overlay_with_transparency(cv::Mat frame, cv::Mat transp, int xPos, int yPos)
{
    cv::Mat mask;
    std::vector<cv::Mat> layers;

    cv::split(transp, layers); // separate channels
    cv::Mat rgb[3] = {layers[0], layers[1], layers[2]};
    mask = layers[3];          // png's alpha channel used as mask
    cv::merge(rgb, 3, transp); // put together the RGB channels, now transp insn't transparent
    transp.copyTo(frame.rowRange(yPos, yPos + transp.rows).colRange(xPos, xPos + transp.cols), mask);
}

int rand_int_in_range(const int range_from, const int range_to)
{
    // from https://stackoverflow.com/a/20136256/15472802
    std::random_device rand_dev;
    std::mt19937 generator(rand_dev());
    std::uniform_int_distribution<int> distr(range_from, range_to);

    return distr(generator);
}

// return a random sample from a vector
template <class T>
T get_random_sample_from(std::vector<T> vec)
{
    // returns 1 random sample, easily modified to return more
    // but doesn't work with nelems = vec.size() to shuffle vec
    // returns samples in the orders they appear in vec

    int num_elems = 1;
    std::vector<T> out;
    std::sample(vec.begin(),
                vec.end(),
                std::back_inserter(out),
                num_elems,
                std::mt19937{std::random_device{}()});

    T result = out[0];
    return result;
}

// return a vector shuffled randomly
template <class T>
std::vector<T> shuffled(std::vector<T> vec)
{
    std::vector<T> out = vec;
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    auto rng = std::default_random_engine(seed);

    std::shuffle(out.begin(),
                 out.end(),
                 rng);
    return out;
}

void make_dobble_card(std::vector<std::string> PICTURES, std::string cardname)
{

    int BKG_WIDTH = 1550;
    int BKG_HEIGHT = 1550;
    int OFFSET = 350;

    cv::Scalar BKG_COLOR(255, 255, 255);

    std::vector<double> ANGLES = {0, 30, 60, 90, 120, 150, 180, 210, 240, 270, 300, 330};
    std::vector<double> SCALES = {0.3, .45, .6};

    int x1 = OFFSET;
    int x3 = BKG_WIDTH / 2;
    int x5 = BKG_WIDTH - OFFSET;
    int x2 = (x1 + x3) / 2 - OFFSET / 5;
    int x4 = (x3 + x5) / 2 + OFFSET / 5;

    int y1 = OFFSET;
    int y3 = BKG_HEIGHT / 2;
    int y5 = BKG_HEIGHT - OFFSET;
    int y2 = (y1 + y3) / 2 + OFFSET / 5;
    int y4 = (y3 + y5) / 2 - OFFSET / 5;

    std::vector<std::vector<int>> POSITIONS = {
        {x2, y1},
        {x4, y1},
        {x1, y3},
        {x3, y2},
        {x5, y3},
        {x3, y4},
        {x2, y5},
        {x4, y5}};

    // shuffle images
    std::vector<std::string> shuffled_pictures = shuffled<std::string>(PICTURES);

    std::cout << std::endl
              << cardname << std::endl;
    for (int i = 0; i < shuffled_pictures.size(); i++)
        std::cout << shuffled_pictures[i] << std::endl;

    cv::Mat output(BKG_HEIGHT, BKG_WIDTH, CV_8UC3, BKG_COLOR);

    for (int k = 0; k < POSITIONS.size(); k++)
    { // get random picture
        std::string picture = shuffled_pictures[k];
        std::string filename = "./assets/selected/" + picture + ".png";
        cv::Mat src = cv::imread(filename, cv::IMREAD_UNCHANGED);

        // random scale and angle
        double angle = get_random_sample_from<double>(ANGLES);
        double scale = get_random_sample_from<double>(SCALES);

        // 1) SCALE

        int new_width = src.cols * scale;
        int new_height = src.rows * scale;
        cv::resize(src, src, cv::Size(new_width, new_height), cv::INTER_LINEAR);

        // 2) TRANSLATE

        int xPos = POSITIONS[k][0];
        int yPos = POSITIONS[k][1];
        xPos -= new_width / 2;
        yPos -= new_height / 2;

        // 3) ROTATE

        // get rotation matrix for rotating the image around its center in pixel coordinates
        cv::Point2f center((src.cols - 1) / 2.0, (src.rows - 1) / 2.0);
        cv::Mat rot = cv::getRotationMatrix2D(center, angle, 1.0);

        // determine bounding rectangle, center not relevant
        cv::Rect2f bbox = cv::RotatedRect(cv::Point2f(), src.size(), angle).boundingRect2f();

        // adjust transformation matrix
        rot.at<double>(0, 2) += bbox.width / 2.0 - src.cols / 2.0;
        rot.at<double>(1, 2) += bbox.height / 2.0 - src.rows / 2.0;

        cv::Mat dst(bbox.height, bbox.width, CV_8UC4);

        cv::warpAffine(src, dst, rot, bbox.size());

        overlay_with_transparency(output, dst, xPos, yPos);
    }

    // draw circle
    cv::Point center(BKG_WIDTH / 2, BKG_HEIGHT / 2);           // Declaring the center point
    int radius = BKG_WIDTH / 2 - OFFSET / 10;                   // Declaring the radius
    cv::Scalar line_Color(0, 0, 0);                            // Color of the circle
    int thickness = 2;                                         // thickness of the line
    cv::circle(output, center, radius, line_Color, thickness); // Using circle()function to draw the line//

    // show image
    // cv::namedWindow("Rotated", cv::WINDOW_AUTOSIZE);
    // cv::imshow("Rotated", output);
    // wait for keystroke
    // cv::waitKey(0);
    cv::imwrite(("./output/" + cardname + ".png"), output);
}

#endif