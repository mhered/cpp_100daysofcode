#include <opencv2/opencv.hpp>
#include <iostream>

#include <chrono>

const double MAX_HEIGHT = 80.0;
const double MAX_WIDTH = 160.0;
const double MONOSPACED_ASPECT_RATIO = 0.5;

template <
    class result_t = std::chrono::milliseconds,
    class clock_t = std::chrono::steady_clock,
    class duration_t = std::chrono::milliseconds>
auto since(std::chrono::time_point<clock_t, duration_t> const &start)
{
    return std::chrono::duration_cast<result_t>(clock_t::now() - start);
}

char int_to_ASCII_char(int value)
{
    const char ASCII_LVL[] = "@#W$97531?!ac;:-,._"; // "$@B%8&WM#*oahkbdpqwmZO0QLCJUYXzcvunxrjft/\\|()1{}[]?-_+~<>i!lI;:,\"^`'."; // "@#W$9876543210?!abc;:+=-,._"; // 
    int length = sizeof(ASCII_LVL) / sizeof(*ASCII_LVL);

    if (value < 0 || value > 255)
        return ' ';

    int index = (length -1) - (int)round((double)value * (length-1) / 255.0);
    return ASCII_LVL[index];
}

void refresh_ASCII_image(cv::Mat frame)
{
    system("clear");
    for (int i = 0; i < frame.rows; i++)
    {
        // char row[frame.cols];
        for (int j = 0; j < frame.cols; j++)
        {
            // int k = frame.at<uchar>(i, j);
            // row[j] = int_to_ASCII_char(k);
            std::cout << int_to_ASCII_char(frame.at<uchar>(i, j));
        }
        std::cout << std::endl;
    }
}

void preprocess_frame(const cv::Mat &frame, cv::Mat &proc_frame, bool forASCII = true)
{
    proc_frame = frame.clone();
    // resize frame to make ASCII display viewable
    double scale = std::min(MAX_WIDTH / (double)frame.cols, MAX_HEIGHT / (double)frame.rows);
    double aspect_ratio = 1.0;
    if (forASCII)
        aspect_ratio = MONOSPACED_ASPECT_RATIO;
    cv::resize(frame, proc_frame, cv::Size(), scale, scale * aspect_ratio, cv::INTER_AREA);
    cv::cvtColor(proc_frame, proc_frame, cv::COLOR_BGR2GRAY);
    // increase contrast x1.5
    proc_frame.convertTo(proc_frame, -1, 1.5, 0);
}

int main()
{
    std::string filename = "sample.mp4";
    filename = ""; // empty filename -> open webcam

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

    // get video properties
    double fps = cap.get(cv::CAP_PROP_FPS); // frames per second

    cv::namedWindow(window_name, cv::WINDOW_NORMAL);

    int keypress = -1;
    bool first_time = true;

    cv::Mat frame;

    while (keypress != ESC_KEY)
    {
        // this to sincro video play with video read
        auto start = std::chrono::steady_clock::now();

        // Try to read a new frame and break the loop if not successful
        if (!cap.read(frame))
        {
            if (filename.empty())
                std::cout << "Video camera is disconnected" << std::endl;
            else
                std::cout << "Found the end of the video" << std::endl;
            break;
        }

        // preprocess frame
        cv::Mat ASCII_frame, show_frame;
        preprocess_frame(frame, ASCII_frame); // to print in terminal
        preprocess_frame(frame, show_frame, false); // to show in window 

        // print out the ASCII image
        refresh_ASCII_image(ASCII_frame);
        imshow(window_name, show_frame);

        // get keypress
        keypress = cv::waitKey(1);

        // wait until it is time to show a new frame to respect FPS
        while (since(start).count() < (1000 / fps))
        {
            continue;
        }
    }
    std::cout << "Stopping the video. Bye!" << std::endl;

    return 0;
}
