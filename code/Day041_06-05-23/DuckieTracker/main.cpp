#include <iostream>
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"

int main(int argc, char **argv)
{
    // cv::VideoCapture cap(0); // capture the video from web cam
    std::string filename = "IMG_1776.MOV";
    cv::VideoCapture cap(filename); // capture from video file

    if (!cap.isOpened()) // if not success, exit program
    {
        std::cout << "Cannot open the video source" << std::endl;
        return -1;
    }

    // initial trackbar settings, good to detect yellow duckie
    int iLowH = 10;
    int iHighH = 60;

    int iLowS = 150;
    int iHighS = 255;

    int iLowV = 105;
    int iHighV = 255;

    // Create trackbars in "Control" window
    cv::namedWindow("Control", cv::WINDOW_AUTOSIZE);
    cv::createTrackbar("LowH", "Control", &iLowH, 179); // Hue (0 - 179)
    cv::createTrackbar("HighH", "Control", &iHighH, 179);

    cv::createTrackbar("LowS", "Control", &iLowS, 255); // Saturation (0 - 255)
    cv::createTrackbar("HighS", "Control", &iHighS, 255);

    cv::createTrackbar("LowV", "Control", &iLowV, 255); // Value (0 - 255)
    cv::createTrackbar("HighV", "Control", &iHighV, 255);

    // For Object tracking
    // create center coordinates
    int iLastX = -1;
    int iLastY = -1;
    // and empty image with same size as video frame
    cv::Mat imgTmp;
    cap.read(imgTmp);

    // Create a black image with the size as the camera output
    cv::Mat imgLines = cv::Mat::zeros(imgTmp.size(), CV_8UC3);

    // create vector to store contours
    std::vector<std::vector<cv::Point>> contours;

    // variabls for annotated image
    cv::Mat imageAnnotated;
    // display colors
    cv::Scalar contColor(0, 255, 0);
    cv::Scalar rectColor(0, 255, 255);

    while (true)
    {
        cv::Mat imgOriginal;

        // try to read a new frame from video
        if (!cap.read(imgOriginal)) // if not success, break loop
        {
            std::cout << "Cannot read a frame from video stream" << std::endl;
            break;
        }

        // Convert the frame from BGR to HSV color space
        cv::Mat imgHSV;
        cvtColor(imgOriginal, imgHSV, cv::COLOR_BGR2HSV);

        // Threshold the image
        cv::Mat imgThresholded;
        cv::inRange(imgHSV,
                    cv::Scalar(iLowH, iLowS, iLowV),
                    cv::Scalar(iHighH, iHighS, iHighV),
                    imgThresholded);

        // morphological opening (remove small objects from the foreground)
        cv::erode(imgThresholded, imgThresholded,
                  cv::getStructuringElement(cv::MORPH_ELLIPSE, cv::Size(5, 5)));
        cv::dilate(imgThresholded, imgThresholded,
                   cv::getStructuringElement(cv::MORPH_ELLIPSE, cv::Size(5, 5)));

        // morphological closing (remove small holes from the foreground)
        cv::dilate(imgThresholded, imgThresholded,
                   cv::getStructuringElement(cv::MORPH_ELLIPSE, cv::Size(5, 5)));
        cv::erode(imgThresholded, imgThresholded,
                  cv::getStructuringElement(cv::MORPH_ELLIPSE, cv::Size(5, 5)));

        // Calculate the moments of the thresholded image
        cv::Moments oMoments = cv::moments(imgThresholded);

        double dM01 = oMoments.m01;
        double dM10 = oMoments.m10;
        double dArea = oMoments.m00;

        // discard if detected area is too small (<= 10000)
        // assumed false detection due to noise
        if (dArea > 10000)
        {
            // calculate the center position of the blob
            int posX = dM10 / dArea;
            int posY = dM01 / dArea;

            if (iLastX >= 0 && iLastY >= 0 && posX >= 0 && posY >= 0)
            {
                // Draw a red line from the previous point to the current point
                cv::line(imgLines, cv::Point(posX, posY),
                         cv::Point(iLastX, iLastY),
                         cv::Scalar(0, 0, 255), 5);
            }
            // update center position
            iLastX = posX;
            iLastY = posY;

            // detect the contours on the binary image using cv2.CHAIN_APPROX_NONE
            std::vector<cv::Vec4i> hierarchy;
            findContours(imgThresholded, contours, hierarchy, cv::RETR_TREE, cv::CHAIN_APPROX_NONE);

            // build bounding rectangles

            // declare aux vectors
            std::vector<std::vector<cv::Point>> contours_poly(contours.size());
            std::vector<cv::Rect> boundRect(contours.size());

            for (size_t i = 0; i < contours.size(); i++) // for each object detected
            {
                // create an approximated polygon from contour, with accuracy 3, and closed
                cv::approxPolyDP(contours[i], contours_poly[i], 3, true);
                boundRect[i] = boundingRect(contours_poly[i]);
            }

            // annotated image: superimpose to the frame
            // the tracking, contours and bounding rectangles
            imageAnnotated = imgOriginal.clone();

            // draw bounding boxes in green if larger than threshold size
            for (size_t i = 0; i < contours.size(); i++)
            {
                if (boundRect[i].area() > 12000)
                {
                    cv::drawContours(imageAnnotated, contours_poly, (int)i, contColor, 2);
                    cv::rectangle(imageAnnotated, boundRect[i].tl(), boundRect[i].br(), rectColor, 5);
                }
            }

            // add track
            imageAnnotated = imageAnnotated + imgLines;
        }

        // show the thresholded image
        cv::imshow("Thresholded Image", imgThresholded);
        cv::imshow("Annotated", imageAnnotated);

        if (cv::waitKey(33) == 27) // wait for 'esc' key press for 33ms. If 'esc' key is pressed, break loop
        {
            std::cout << "esc key is pressed by user" << std::endl;
            break;
        }
    }

    // display thresholds
    std::cout << "int iLowH = " << iLowH << ";" << std::endl;
    std::cout << "int iHighH = " << iHighH << ";" << std::endl;

    std::cout << "int iLowS = " << iLowS << ";" << std::endl;
    std::cout << "int iHighS = " << iHighS << ";" << std::endl;

    std::cout << "int iLowV = " << iLowV << ";" << std::endl;
    std::cout << "int iHighV = " << iHighV << ";" << std::endl;

    return 0;
}