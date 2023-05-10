#include <opencv4/opencv2/opencv.hpp>
#include "FaceDetector.h"

#include <iomanip>
#include <sstream>

int main()
{

    //

    // open vide source
    cv::VideoCapture video_capture;
    if (!video_capture.open("sample.mp4")) // if (!video_capture.open(0))  // web cam
    {
        return 0;
    }

    FaceDetector face_detector;

    cv::Mat frame;

    // format rectangles
    cv::Scalar COLOR_BOX(0, 255, 0); // green
    int FRAME_THICKNESS = 2;

    // format text
    cv::Scalar COLOR_TEXT(0, 225, 0); // green
    int FONT_FACE = cv::FONT_HERSHEY_COMPLEX;
    float FONT_SIZE = 1.0;

    const int ESC_KEY = 27;
    const int SPACE_KEY = 32;

    bool first_time = true;
    while (true)
    {
        // capture frame
        video_capture >> frame;

        // prepare variables and detect faces
        std::vector<cv::Rect> rectangles;
        std::vector<float> confidences;
        face_detector.detect_face_rectangles(frame, rectangles, confidences);

        // display rectangles and confidence level
        for (int i = 0; i < rectangles.size(); i++)
        {
            // show rectangle
            cv::rectangle(frame, rectangles[i], COLOR_BOX, FRAME_THICKNESS);

            // update text and position
            std::stringstream stream;
            stream << std::fixed << std::setprecision(2) << 100 * confidences[i] << "%"; // 0.945677 -> "94.57%"
            std::string text = stream.str();
            cv::Point text_position(rectangles[i].x + 10, rectangles[i].y + rectangles[i].height - 10);

            // show text
            cv::putText(frame, text, text_position, FONT_FACE, FONT_SIZE, COLOR_TEXT);
        }

        imshow("Video Source | SPACE to start | ESC to close", frame);

        if (first_time)
        {
            while (true)
                if (cv::waitKey(10) == SPACE_KEY)
                {
                    first_time = false;
                    break;
                }
        }

        if (cv::waitKey(10) == ESC_KEY)
        {
            break;
        }
    }
    cv::destroyAllWindows();
    video_capture.release();
    return 0;
}