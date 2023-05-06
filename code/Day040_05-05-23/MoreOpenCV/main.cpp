#include <opencv2/opencv.hpp>
#include <iostream>

#include <chrono>

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
    // std::string filename = "final_explosion.mp4";
    std::string filename = "IMG_1776.MOV";
    // filename = ""; // empty filename -> open webcam
    std::string window_name = filename;

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
    window_name += "- Press ESC to exit";
    cv::namedWindow(window_name, cv::WINDOW_NORMAL);
    // needed to get a nice initial display,
    // without this the window is smaller that the image
    cv::resizeWindow(window_name, d_width, d_height);

    int keypress = -1;

    while (keypress != 27)
    {
        // this to sincro video play with video read
        auto start = std::chrono::steady_clock::now();

        cv::Mat frame;
        cv::Mat mod_frame;

        // Try to read a new frame and break the loop if not successful
        if (!cap.read(frame))
        {
            if (filename.empty())
                std::cout << "Video camera is disconnected" << std::endl;
            else
                std::cout << "Found the end of the video" << std::endl;
            break;
        }

        // resize frame to make processing manageable
        // downscale to <= 480x320 maintaining aspect ratio
        int HEIGHT = 320;
        int WIDTH = 480;
        double scale = std::min(WIDTH / d_width, HEIGHT / d_height);
        cv::resize(frame, mod_frame, cv::Size(), scale, scale, cv::INTER_AREA);

        // std::cout << "frame: " << frame.cols << " x " << frame.rows << std::flush;
        // std::cout << " | mod_frame: " << mod_frame.cols << " x " << mod_frame.rows << std::endl;

        if (keypress == 99) // "c" to increase contrast 1.5 times
        {
            mod_frame.convertTo(mod_frame, -1, 1.5, 0);
            cv::putText(mod_frame, "Increased contrast",
                        cv::Point(50, 50),
                        cv::FONT_HERSHEY_DUPLEX,
                        1.0,
                        cv::Scalar(255, 225, 255));
        }
        else if (keypress == 98) // "b" to decrease brightness by 100
        {
            mod_frame.convertTo(mod_frame, -1, 1, -100);
            cv::putText(mod_frame, "Decreased brightness",
                        cv::Point(50, 50),
                        cv::FONT_HERSHEY_DUPLEX,
                        1.0,
                        cv::Scalar(255, 225, 255));
        }
        else if (keypress == 103) // "g" to apply Gaussian blur 5x5
        {
            cv::GaussianBlur(mod_frame, mod_frame, cv::Size(5, 5), 0);
            cv::putText(mod_frame, "Gaussian blur 5x5",
                        cv::Point(50, 50),
                        cv::FONT_HERSHEY_DUPLEX,
                        1.0,
                        cv::Scalar(255, 225, 255));
        }
        else if (keypress == 104) // "h" - apply histogram equalization
        {
            // Convert the frame from BGR to YCrCb color space
            // otherwise we lose colour information
            cv::cvtColor(mod_frame, mod_frame, cv::COLOR_BGR2YCrCb);

            // Split the frame image into 3 channels, respectively Y, Cr and Cb
            // and store it in a std::vector
            // only Y contains intensity data that needs equalization
            std::vector<cv::Mat> vec_channels;
            cv::split(mod_frame, vec_channels);

            // Equalize the histogram of only the Y channel
            cv::equalizeHist(vec_channels[0], vec_channels[0]);

            // Merge 3 channels back into a color image in YCrCB color space
            cv::merge(vec_channels, mod_frame);

            // Convert back from YCrCb to BGR color space
            cvtColor(mod_frame, mod_frame, cv::COLOR_YCrCb2BGR);
            cv::putText(mod_frame, "Hist-eq",
                        cv::Point(50, 50),
                        cv::FONT_HERSHEY_DUPLEX,
                        1.0,
                        cv::Scalar(255, 225, 255));
        }
        else if (keypress == 32) // save current frame if SPACE pressed
        {
            std::cout << "Saving frame..." << std::endl;
            // extension used to determine format
            // remember OpenCV uses BGR order of channels internally!
            bool success = cv::imwrite("frame.jpg", mod_frame);

            if (!success)
            {
                std::cout << "Failed to save the frame" << std::endl;
                return -1;
            }
            std::cout << "Frame succesfully saved to frame.jpg" << std::endl;
        }
        else if (keypress == 112) // "p" for pause
        {
            char a;
            std::cout << "PAUSED. Press ENTER to resume." << std::endl;
            while (true)
            {
                if (cv::waitKey(1) == 13) // ENTER to resume
                    break;
            }
        }
        else
        {
            if (keypress != -1)
                std::cout << "You pressed: " << keypress << "(" << (char)keypress << ")" << std::endl;
        }

        // show the processed frame in the window
        cv::imshow(window_name, mod_frame);

        // wait until it is time to show a new frame to respect FPS
        while (since(start).count() < (1000 / fps))
        {
            keypress = cv::waitKey(33); // works well with 33 but not lower values
        }
    }
    std::cout << "Stopping the video. Bye!" << std::endl;

    return 0;
}