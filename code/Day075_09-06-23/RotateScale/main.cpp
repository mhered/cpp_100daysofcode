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
    auto rng=std::default_random_engine(seed);

    std::shuffle(out.begin(),
                 out.end(),
                 rng);
    return out;
}

int main()
{

    int BKG_WIDTH = 1500;
    int BKG_HEIGHT = 1500;
    int OFFSET = 200;
    int M = 3;
    int N = 3;

    cv::Scalar BKG_COLOR(255, 255, 255); // Tomato (52, 58, 235)

    std::vector<std::string> PICTURES = {
        "apple",
        "gamepad",
        "rubik",
        "basketball",
        "robot",
        "sunglasses",
        "color-pencil",
        "rocket",
        "tyrannosaurus-rex",
    };

    std::vector<double> ANGLES = {0, 30, 60, 90, 120, 150, 180, 210, 240, 270, 300, 330};
    std::vector<double> SCALES = {0.2, .4, .6};

    std::vector<std::vector<int>> POSITIONS;
    for (int i = 0; i < M; i++)
    {
        for (int j = 0; j < N; j++)
        {
            int x = j * (BKG_WIDTH - 2 * OFFSET) / N + (BKG_WIDTH - 2 * OFFSET) / (N * 2) + OFFSET;
            int y = i * (BKG_HEIGHT - 2 * OFFSET) / M + (BKG_HEIGHT - 2 * OFFSET) / (M * 2) + OFFSET;
            POSITIONS.push_back({x, y});
        }
    }

    // shuffle images
    std::vector<std::string> shuffled_pictures = shuffled<std::string>(PICTURES);

    for (int i = 0; i < shuffled_pictures.size(); i++)
        std::cout << shuffled_pictures[i] << std::endl;

    cv::Mat output(BKG_HEIGHT, BKG_WIDTH, CV_8UC3, BKG_COLOR);

    for (int k = 0; k < (M * N); k++)
    { // get random picture
        std::string picture = shuffled_pictures[k];
        std::string filename = "./assets/" + picture + ".png";
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

    // show image
    cv::namedWindow("Rotated", cv::WINDOW_AUTOSIZE);
    cv::imshow("Rotated", output);
    // wait for keystroke
    cv::waitKey(0);

    // cv::imwrite("output.png", output);

    return 0;
}
