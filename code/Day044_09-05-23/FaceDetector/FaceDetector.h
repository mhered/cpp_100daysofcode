#ifndef FACEDETECTOR_H
#define FACEDETECTOR_H

#include <opencv4/opencv2/dnn.hpp>

#pragma once

class FaceDetector
{
public:
    explicit FaceDetector();
    // Detect faces in an image frame
    // `frame` Image to detect faces in
    // `rectangles` (return by reference) Vector of detected faces 
    // `confidences` (return by reference) Vector of confidence levels 
    void detect_face_rectangles(const cv::Mat &frame, std::vector<cv::Rect> &rectangles, std::vector<float> &confidences);

private:
    // Face detection network
    cv::dnn::Net network_;
    // Input image width
    const int input_image_width_;
    // Input image height
    const int input_image_height_;
    // Scale factor when creating image blob
    const double scale_factor_;
    // Mean normalization values network was trained with
    const cv::Scalar mean_values_;
    // Face detection confidence threshold
    const float confidence_threshold_;
};

#endif