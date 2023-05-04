#include <opencv2/highgui.hpp>
#include <iostream>

bool show_image(std::string filename, std::string window_name)
{
    bool success = false;

    cv::Mat image;
    image = cv::imread(filename, cv::IMREAD_COLOR); // IMREAD_GRAYSCALE, IMREAD_COLOR (note color order is BGR not RGB!!), IMREAD_UNCHANGED needed for alpha channel
    if (image.empty())
    {
        std::cout << "Could not open or find the image \"" << filename << "\" I'll show you Tomato." << std::endl;
        // create a new image
        // 3 x 8 bits channels
        // 640 x 480 resolution (640 wide and 480 high)
        // each pixel initialized to the value of (52, 58, 235) for Blue, Green and Red planes respectively. (BGR not RGB!!)
        // e.g. RGB: 235, 58, 52  -> BGR: 52, 58, 235
        cv::Mat image2(480, 640, CV_8UC3, cv::Scalar(52, 58, 235));
        image = image2;
        window_name = "Tomato"; // Name of the window
    }

    // create a window
    cv::namedWindow(window_name, cv::WINDOW_NORMAL); // WINDOW_NORMAL can resize, WINDOW_AUTOSIZE cannot
    // show image inside the window
    cv::imshow(window_name, image);
    // wait for keystroke
    cv::waitKey(0);
    // destroy the window not necessary, it is destroyed when out of scope
    // cv::destroyWindow(window_name);
    success = true;
    return success;
}

int main(int argc, char **argv)
{
    /* // checking command line arguments
    std::cout << argc << " arguments\n";
    for (int i = 0; i < argc; ++i)
        std::cout << argv[i] << "\n";
    */

    std::string filename = "";
    std::string window_name = "";

    if (argc >= 2) // filename provided
    {
        std::string str(argv[1]); // use constructor to assign char* to std::string
        filename = str;
        window_name = str;
    }
    if (argc >= 3) // window_name provided
    {
        std::string str(argv[2]); // use constructor to assign char* to std::string
        window_name = str;
    }
    show_image(filename, window_name);
}
