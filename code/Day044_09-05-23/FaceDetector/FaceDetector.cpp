#include <sstream>
#include <vector>
#include <string>
#include "FaceDetector.h"
#include <opencv4/opencv2/opencv.hpp>

// Constructor
// To achieve the best accuracy run the model on BGR images resized to 300x300
// applying mean subtraction of values (104, 177, 123) for each blue, green and red channels correspondingly.

FaceDetector::FaceDetector() : confidence_threshold_(0.5),
                               input_image_height_(300),
                               input_image_width_(300),
                               scale_factor_(1.0),
                               mean_values_({104., 177.0, 123.0})
{

    // variables to keep paths of model files
    std::string PWD = "./models/";
    std::string FACE_DETECTION_CONFIG = PWD + "deploy.prototxt";
    std::string FACE_DETECTION_WEIGHTS = PWD + "res10_300x300_ssd_iter_140000_fp16.caffemodel";

    network_ = cv::dnn::readNetFromCaffe(FACE_DETECTION_CONFIG, FACE_DETECTION_WEIGHTS);

    if (network_.empty())
    {
        std::ostringstream ss;
        ss << "Failed to load network with the following settings:\n"
           << "Configuration: " + std::string(FACE_DETECTION_CONFIG) + "\n"
           << "Binary: " + std::string(FACE_DETECTION_WEIGHTS) + "\n";
        throw std::invalid_argument(ss.str());
    }
}

void FaceDetector::detect_face_rectangles(const cv::Mat &frame, std::vector<cv::Rect> &faces, std::vector<float> &confidences)
{

    // To achieve the best accuracy run the model on BGR images resized to 300x300
    // applying mean subtraction of values (104, 177, 123) for each blue, green and red channels correspondingly.

    cv::Mat input_blob = cv::dnn::blobFromImage(frame,
                                                scale_factor_,
                                                cv::Size(input_image_width_, input_image_height_),
                                                mean_values_,
                                                false,
                                                false);

    // a 4-D array is returned which contains the confidence and coordinates scaled down to the range of 0 to 1
    // such that by multiplying them by the original width and height predictions can be obtained for the original image
    // as opposed to the 300x300 on which the model predicted.

    network_.setInput(input_blob, "data");
    cv::Mat detection = network_.forward("detection_out");
    cv::Mat detection_matrix(detection.size[2],
                             detection.size[3],
                             CV_32F,
                             detection.ptr<float>());

    for (int i = 0; i < detection_matrix.rows; i++)
    {
        float confidence = detection_matrix.at<float>(i, 2);

        if (confidence < confidence_threshold_) // skip detections below threshold
        {
            continue;
        }

        confidences.push_back(confidence);
        
        int x_left_bottom = static_cast<int>(
            detection_matrix.at<float>(i, 3) * frame.cols);

        int y_left_bottom = static_cast<int>(
            detection_matrix.at<float>(i, 4) * frame.rows);

        int x_right_top = static_cast<int>(
            detection_matrix.at<float>(i, 5) * frame.cols);

        int y_right_top = static_cast<int>(
            detection_matrix.at<float>(i, 6) * frame.rows);

        faces.emplace_back(x_left_bottom,
                           y_left_bottom,
                           (x_right_top - x_left_bottom),
                           (y_right_top - y_left_bottom));
    }
}
