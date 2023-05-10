#include <iostream>
#include <opencv2/opencv.hpp>
#include <iostream>
#include <chrono>

#include "Blob.h"

// define colors
const cv::Scalar COLOR_BLACK = cv::Scalar(0.0, 0.0, 0.0);
const cv::Scalar COLOR_WHITE = cv::Scalar(255.0, 255.0, 255.0);
const cv::Scalar COLOR_BLUE = cv::Scalar(255.0, 0.0, 0.0);
const cv::Scalar COLOR_GREEN = cv::Scalar(0.0, 200.0, 0.0);
const cv::Scalar COLOR_RED = cv::Scalar(0.0, 0.0, 255.0);
const cv::Scalar COLOR_YELLOW = cv::Scalar(0.0, 250.0, 255.0);
const cv::Scalar COLOR_CYAN = cv::Scalar(255.0, 255.0, 0.0);

// define conditions for valid convex hulls
const int MIN_AREA = 100;
const double MIN_ASPECT_RATIO = 0.2;
const double MAX_ASPECT_RATIO = 1.2;
const int MIN_BOX_WIDTH = 15;
const int MIN_BOX_HEIGHT = 20;
const double MIN_BOX_DIAGONAL = 30.0;

void Preprocess_frame(const cv::Mat &frame, cv::Mat &proc_frame)
{
    proc_frame = frame.clone();
    cv::cvtColor(proc_frame, proc_frame, cv::COLOR_BGR2GRAY);
    cv::GaussianBlur(proc_frame, proc_frame, cv::Size(5, 5), 0);
}

template <
    class result_t = std::chrono::milliseconds,
    class clock_t = std::chrono::steady_clock,
    class duration_t = std::chrono::milliseconds>
auto since(std::chrono::time_point<clock_t, duration_t> const &start)
{
    return std::chrono::duration_cast<result_t>(clock_t::now() - start);
}

int main(int argc, char *argv[])
{
    std::string filename = "imagesubtraction.mp4"; // "768x576.avi";
    // filename = ""; // empty filename -> open webcam

    std::string window_name = filename;

    const int ESC_KEY = 27;
    const int SPACE_KEY = 32;
    const int ENTER_KEY = 13;

    // if filename provided open the video file for reading otherwise open default camera
    // using if/else + 2 different constructors + copy constructor (implicitly)
    // needed due to scoping, but it seems complicated for a rather simple thing!
    cv::VideoCapture cap;
    if (filename.empty())
    {
        cap = cv::VideoCapture(0);
        window_name = "Default camera";
    }
    else
        cap = cv::VideoCapture(filename);

    if (cap.isOpened() == false) //  if not success, exit program
    {
        std::cout << "Cannot open video source \"" << window_name << "\"" << std::endl;
        return -1;
    }

    // get and print out video properties
    double d_width = cap.get(cv::CAP_PROP_FRAME_WIDTH);   // video frame width
    double d_height = cap.get(cv::CAP_PROP_FRAME_HEIGHT); // video frame height
    double fps = cap.get(cv::CAP_PROP_FPS);               // frames per second

    std::cout << d_width << " x " << d_height << " pixels resolution, " << fps << " frames per second" << std::endl;

    // create a window
    window_name += " | Press SPACE to pause/resume | Press ESC to exit";
    cv::namedWindow(window_name, cv::WINDOW_NORMAL);
    // needed to get a nice initial display,
    // without this the window is smaller than the image
    cv::resizeWindow(window_name, d_width, d_height);

    int keypress = -1;
    bool first_time = true;

    cv::Mat frame1, frame2;
    cap.read(frame1);

    while (keypress != ESC_KEY)
    {
        // this to sincro video play with video read
        auto start = std::chrono::steady_clock::now();

        // Try to read a new frame and break the loop if not successful
        if (!cap.read(frame2))
        {
            if (filename.empty())
                std::cout << "Video camera is disconnected" << std::endl;
            else
                std::cout << "Found the end of the video" << std::endl;
            break;
        }

        // preprocess 2 frames
        cv::Mat proc_frame1, proc_frame2;
        Preprocess_frame(frame1, proc_frame1);
        Preprocess_frame(frame2, proc_frame2);

        // subtract them
        cv::Mat gray_diff;
        cv::absdiff(proc_frame1, proc_frame2, gray_diff);

        // apply threshold to the difference
        cv::Mat thres_diff;
        cv::threshold(gray_diff, thres_diff, 30, 255.0, cv::THRESH_BINARY);

        // apply dilate x2 + erode to a copy of the thresholded difference
        cv::Mat structuringElement5x5 = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(5, 5));
        cv::Mat thres_diff_cp = thres_diff.clone();

        cv::dilate(thres_diff_cp, thres_diff_cp, structuringElement5x5);
        cv::dilate(thres_diff_cp, thres_diff_cp, structuringElement5x5);
        cv::erode(thres_diff_cp, thres_diff_cp, structuringElement5x5);

        // find contours
        std::vector<std::vector<cv::Point>> contours;
        cv::findContours(thres_diff_cp, contours, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);

        // draw contours
        // make empty black image of frame size
        cv::Mat draw_contours(thres_diff.size(), CV_8UC3, COLOR_BLACK);
        cv::drawContours(draw_contours, contours, -1, COLOR_GREEN, -1);
        // contour # = -1 -> draw all contours
        // thickness <0  -> fill area bounded by contours

        // make a convex hull for each contour
        std::vector<std::vector<cv::Point>> convex_hulls(contours.size());
        for (unsigned int i = 0; i < contours.size(); i++)
        {
            cv::convexHull(contours[i], convex_hulls[i]);
        }

        // check one by one agaist validity conditions
        std::vector<Blob> blobs;
        for (auto &convex_hull : convex_hulls)
        {
            Blob candidate(convex_hull);

            if (candidate.rect.area() > MIN_AREA &&
                candidate.aspect_ratio >= MIN_ASPECT_RATIO &&
                candidate.aspect_ratio <= MAX_ASPECT_RATIO &&
                candidate.rect.width > MIN_BOX_WIDTH &&
                candidate.rect.height > MIN_BOX_HEIGHT &&
                candidate.diagonal > MIN_BOX_DIAGONAL)
            {
                blobs.push_back(candidate); // add only valid Blobs to vector
            }
        }

        // clear convex_hulls and reload, this time valid blobs only
        convex_hulls.clear();
        for (auto &blob : blobs)
        {
            convex_hulls.push_back(blob.contour);
        }

        // draw convex_hulls
        // make empty black image of frame size
        cv::Mat draw_convex_hulls(thres_diff.size(), CV_8UC3, COLOR_BLACK);
        cv::drawContours(draw_convex_hulls, convex_hulls, -1, COLOR_CYAN, -1);
        // contour # = -1 -> draw all contours
        // thickness <0  -> fill area bounded by contours

        // annotate rectangles on frame2
        cv::Mat frame2_cp = frame2.clone(); // get another copy of frame1

        for (auto &blob : blobs) // for each blob
        {
            // draw a red box around the blob
            cv::rectangle(frame2_cp, blob.rect, COLOR_YELLOW, 2);
            // draw a filled-in green circle at the center
            cv::circle(frame2_cp, blob.centre, 3, COLOR_RED, -1);
        }

        // make composite image with 4 steps
        cv::Mat composite, composite1, composite2, gray_diff_3;
        cv::cvtColor(gray_diff, gray_diff_3, cv::COLOR_GRAY2BGR); // need 3 channels
        cv::hconcat(gray_diff_3, draw_contours, composite1);
        cv::hconcat(draw_convex_hulls, frame2_cp, composite2);
        cv::vconcat(composite1, composite2, composite);

        // show the processed frame in the window
        cv::imshow(window_name, composite);

        // prepare next iteration
        frame1 = frame2.clone();

        // get keypress
        keypress = cv::waitKey(1);

        if (first_time || keypress == SPACE_KEY) // SPACE to pause
        {
            char a;
            while (true)
            {
                if (cv::waitKey(1) == SPACE_KEY) // SPACE to resume
                {
                    first_time = false;
                    break;
                }
            }
        }

        // wait until it is time to show a new frame to respect FPS
        while (since(start).count() < (1000 / fps))
        {
            continue;
        }
    }
    std::cout << "Stopping the video. Bye!" << std::endl;

    return 0;
}
