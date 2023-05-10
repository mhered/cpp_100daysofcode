#include "Blob.h"
#include <cmath>

Blob::Blob(std::vector<cv::Point> _contour)
{

    contour = _contour;

    rect = cv::boundingRect(contour);

    centre.x = rect.x + rect.width / 2;
    centre.y = rect.y + rect.height / 2;

    diagonal = sqrt(pow(rect.width, 2) + pow(rect.height, 2));

    aspect_ratio = (double)rect.width / (double)rect.height;
}