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
const int MIN_AREA = 150;
const double MIN_ASPECT_RATIO = 0.2;
const double MAX_ASPECT_RATIO = 1.2;
const int MIN_BOX_WIDTH = 15;
const int MIN_BOX_HEIGHT = 35;
const double MIN_BOX_DIAGONAL = 30.0;

////////////////////////////////////////////////////////////////////////////////
void preprocess_frame(const cv::Mat &frame, cv::Mat &proc_frame)
{
    proc_frame = frame.clone();
    cv::cvtColor(proc_frame, proc_frame, cv::COLOR_BGR2GRAY);
    cv::GaussianBlur(proc_frame, proc_frame, cv::Size(5, 5), 0);
}

////////////////////////////////////////////////////////////////////////////////
template <
    class result_t = std::chrono::milliseconds,
    class clock_t = std::chrono::steady_clock,
    class duration_t = std::chrono::milliseconds>
auto since(std::chrono::time_point<clock_t, duration_t> const &start)
{
    return std::chrono::duration_cast<result_t>(clock_t::now() - start);
}

////////////////////////////////////////////////////////////////////////////////
void match_with_existing_blob(Blob &blob, std::vector<Blob> &existing_blobs, int &index)
{

    existing_blobs[index].contour = blob.contour; // update contour
    existing_blobs[index].rect = blob.rect;       // update rectangle

    existing_blobs[index].positions.push_back(blob.positions.back()); // add last position

    existing_blobs[index].diagonal = blob.diagonal;         // update diagonal
    existing_blobs[index].aspect_ratio = blob.aspect_ratio; // update aspect ratio

    existing_blobs[index].being_tracked = true; // set flag to tracked and matched
    existing_blobs[index].match_or_new = true;
}

////////////////////////////////////////////////////////////////////////////////
void add_new_blob(Blob &new_blob, std::vector<Blob> &existing_blobs)
{

    new_blob.match_or_new = true; // set flag to true

    existing_blobs.push_back(new_blob);
}

////////////////////////////////////////////////////////////////////////////////
double distance_between_pts(cv::Point pt1, cv::Point pt2)
{

    int x = abs(pt1.x - pt2.x);
    int y = abs(pt1.y - pt2.y);

    return (sqrt(pow(x, 2) + pow(y, 2)));
}

////////////////////////////////////////////////////////////////////////////////
void match_frame_blobs_to_existing_blobs(std::vector<Blob> &existing_blobs, std::vector<Blob> &frame_blobs)
{
    for (auto &blob : existing_blobs) // for each existing blob
    {
        blob.match_or_new = false; // set flag to false to force matching
        blob.predict_next_pos();   // updates blob.predicted_next_pos
    }

    for (auto &blob : frame_blobs) // for each blob in the frame
    {

        int index_closest_blob = 0;
        double min_distance = 100000.0;

        for (std::size_t i = 0; i < existing_blobs.size(); i++)
        {
            // find the closest existing blob that is being tracked
            if (existing_blobs[i].being_tracked == true)
            {
                // calculate distance between the last position of the frame blob
                // and next predicted position of each existing blob
                double distance = distance_between_pts(blob.positions.back(),
                                                       existing_blobs[i].predicted_next_pos);
                if (distance < min_distance)
                {
                    min_distance = distance;
                    index_closest_blob = i;
                }
            }
        }

        if (min_distance < blob.diagonal * 1.15) // compares distance to diagonal
        {
            match_with_existing_blob(blob, existing_blobs, index_closest_blob);
        }
        else
        {
            add_new_blob(blob, existing_blobs);
        }
    }

    for (auto &blob : existing_blobs)
    {

        if (blob.match_or_new == false) // blobs not matched: increment # of frames not matched
        {
            blob.frames_without_match++;
        }

        if (blob.frames_without_match >= 10) // if >10 frames not matched stop tracking
        {
            blob.being_tracked = false;
        }
    }
}

////////////////////////////////////////////////////////////////////////////////
void draw_blobs_on_image(std::vector<Blob> &blobs, cv::Mat &frame)
{

    for (std::size_t i; i < blobs.size(); i++) // for each blob
    {
        if (blobs[i].being_tracked == true)
        {
            //  draw a yellow box around the blob
            cv::rectangle(frame, blobs[i].rect, COLOR_YELLOW, 2);

            int font_face = cv::FONT_HERSHEY_COMPLEX;
            double font_scale = blobs[i].diagonal / 60.0;
            int font_thickness = (int)std::round(font_scale * 1.0);

            cv::putText(frame, std::to_string(i), blobs[i].positions.back(),
                        font_face, font_scale, COLOR_GREEN, font_thickness);

            // draw a green line of last 10 positions
            // cv::circle(frame, blobs[i].positions.back(), 3, COLOR_RED, -1);
        }
    }
}

////////////////////////////////////////////////////////////////////////////////
int main(int argc, char *argv[])
{
    std::string filename = "input.mp4"; // "768x576.avi";
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

    std::vector<Blob> blobs;

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
        preprocess_frame(frame1, proc_frame1);
        preprocess_frame(frame2, proc_frame2);

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
        for (std::size_t i = 0; i < contours.size(); i++)
        {
            cv::convexHull(contours[i], convex_hulls[i]);
        }

        // check one by one agaist validity conditions
        std::vector<Blob> frame_blobs;
        for (auto &convex_hull : convex_hulls)
        {
            Blob candidate(convex_hull);

            if (candidate.rect.area() > MIN_AREA &&
                candidate.aspect_ratio >= MIN_ASPECT_RATIO &&
                candidate.aspect_ratio <= MAX_ASPECT_RATIO &&
                candidate.rect.width > MIN_BOX_WIDTH &&
                candidate.rect.height > MIN_BOX_HEIGHT &&
                candidate.diagonal > MIN_BOX_DIAGONAL &&
                // new condition
                (cv::contourArea(candidate.contour) / (double)candidate.rect.area()) > 0.40)
            {
                frame_blobs.push_back(candidate); // add only valid Blobs to vector
            }
        }

        // first time populate blob vector. Subsequent times match with existing blobs
        if (first_time == true)
        {
            for (auto &blob : frame_blobs)
            {
                blobs.push_back(blob);
            }
        }
        else
        {
            // need to write
            match_frame_blobs_to_existing_blobs(blobs, frame_blobs);
        }

        // clear convex_hulls and reload, this time valid blobs being tracked only
        convex_hulls.clear();
        for (auto &blob : blobs)
        {
            if (blob.being_tracked)
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

        draw_blobs_on_image(blobs, frame2_cp);

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
