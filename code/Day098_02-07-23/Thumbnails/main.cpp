#include <iostream>
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"

#include <filesystem>

namespace fs = std::filesystem; // requires -std=c++17

// create thumbnail from image or video
bool Thumbnail(fs::path img_path,
               const fs::path tmb_path,
               const int MAX_WIDTH = 200,
               const int MAX_HEIGHT = 200,
               bool verbose = false)
{
    cv::Mat image, tmb_image;

    // try to open as image
    image = cv::imread(img_path.string(), cv::IMREAD_COLOR);

    if (image.empty())
    {
        if (verbose)
        {
            std::cout << "Could not open or find an image in " << img_path << std::endl;

            std::cout << "Attempting to open it as a video source... " << std::endl;
        }
        // try to open as video
        cv::VideoCapture cap(img_path.string());
        int length = static_cast<int>(cap.get(cv::CAP_PROP_FRAME_COUNT));

        // make thumbnail from the frame at 10% of the duration
        cap.set(cv::CAP_PROP_POS_FRAMES, length / 10);
        cap.grab();

        // Try to get and save frame
        if (!cap.retrieve(image))
        {
            if (verbose)
                std::cout << "Could not open or find a video in " << img_path << std::endl;

            return false;
        }
    }

    // get image dimensions
    int width = image.size().width;
    int height = image.size().height;

    // scale respecting aspect ratio
    // so that both dimensions fit in the maximum dimensions provided
    double fscale = std::min((1.0 * MAX_WIDTH) / width, (1.0 * MAX_HEIGHT) / height);

    cv::resize(image,
               tmb_image,
               cv::Size(),
               fscale,
               fscale,
               cv::INTER_AREA);

    // create thumbnail filename
    std::string tmb_filename = "tmb_" + img_path.stem().string() + ".jpg";

    if (verbose)
        std::cout << "Saving " << tmb_image.size().width
                  << " by " << tmb_image.size().height
                  << " thumbnail to: " << (tmb_path / tmb_filename) << std::endl;

    // save thumbnail in the path provided
    cv::imwrite((tmb_path / tmb_filename).string(), tmb_image);
    return true;
}

int main()
{
    fs::path path = fs::current_path() / "images";
    fs::path tmb_path = fs::current_path() / "thumbnails";
    bool verbose = true;
    const int MAX_HEIGHT = 200;
    const int MAX_WIDTH = 200;

    // Check if thumbnails folder exists, if not create it
    if (!fs::is_directory("thumbnails") || !fs::exists("thumbnails"))
    {
        fs::create_directory("thumbnails");
    }

    // scan directory for files
    for (const auto &entry : fs::directory_iterator(path))
    {
        if (entry.is_regular_file())
        {
            if (Thumbnail(entry, tmb_path, MAX_HEIGHT, MAX_WIDTH, verbose) && verbose)
                std::cout << "Thumbnail saved to: " << tmb_path << std::endl;
        }
    }
    return 0;
}