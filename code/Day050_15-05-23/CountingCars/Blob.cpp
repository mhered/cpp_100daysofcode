#include "Blob.h"
#include <cmath>

// initialize static variables
std::vector<cv::Scalar> Blob::COLORS =
        {
            COLOR_BLUE,
            COLOR_GREEN,
            COLOR_DARK_GREEN,
            COLOR_RED,
            COLOR_YELLOW,
            COLOR_CYAN,
            COLOR_ORANGE,
            COLOR_PINK,
            COLOR_VIOLET,
            COLOR_BROWN};

int Blob::count =0;

Blob::Blob(std::vector<cv::Point> _contour)
{

    contour = _contour;

    rect = cv::boundingRect(contour);

    cv::Point centre;

    centre.x = rect.x + rect.width / 2;
    centre.y = rect.y + rect.height / 2;

    // save centre position in history
    positions.push_back(centre);

    diagonal = sqrt(pow(rect.width, 2) + pow(rect.height, 2));

    aspect_ratio = (double)rect.width / (double)rect.height;

    // initialize variables related to tracking the blob
    match_or_new = true;
    being_tracked = true;
    frames_without_match = 0;

    // set color
    ++count; // increment count
    color = COLORS[count%COLORS.size()];
    // std::cout << "Assigned color #" << count%COLORS.size() << " :" << color <<std::endl;
}

void Blob::predict_next_pos(void)
{
    int n = positions.size();

    if (n == 1)
    {
        predicted_next_pos.x = positions.back().x;
        predicted_next_pos.y = positions.back().y;
    }
    else if (n == 2)
    {

        int sumOfXChanges = ((positions[n - 1].x - positions[n - 2].x) * 1);
        int sumOfYChanges = ((positions[n - 1].y - positions[n - 2].y) * 1);

        int deltaX = (int)std::round((float)sumOfXChanges);
        int deltaY = (int)std::round((float)sumOfYChanges);

        predicted_next_pos.x = positions.back().x + deltaX;
        predicted_next_pos.y = positions.back().y + deltaY;
    }
    else if (n >= 3)
    {

        int sumOfXChanges = ((positions[n - 1].x - positions[n - 2].x) * 2) +
                            ((positions[n - 2].x - positions[n - 3].x) * 1);

        int sumOfYChanges = ((positions[n - 1].y - positions[n - 2].y) * 2) +
                            ((positions[n - 2].y - positions[n - 3].y) * 1);

        int deltaX = (int)std::round((float)sumOfXChanges / 3.0);
        int deltaY = (int)std::round((float)sumOfYChanges / 3.0);

        predicted_next_pos.x = positions.back().x + deltaX;
        predicted_next_pos.y = positions.back().y + deltaY;
    }
    // no need to include so many points in the prediction
    else if (n == 4)
    {

        int sumOfXChanges = ((positions[n - 1].x - positions[n - 2].x) * 3) +
                            ((positions[n - 2].x - positions[n - 3].x) * 2) +
                            ((positions[n - 3].x - positions[n - 4].x) * 1);

        int sumOfYChanges = ((positions[n - 1].y - positions[n - 2].y) * 3) +
                            ((positions[n - 2].y - positions[n - 3].y) * 2) +
                            ((positions[n - 3].y - positions[n - 4].y) * 1);

        int deltaX = (int)std::round((float)sumOfXChanges / 6.0);
        int deltaY = (int)std::round((float)sumOfYChanges / 6.0);

        predicted_next_pos.x = positions.back().x + deltaX;
        predicted_next_pos.y = positions.back().y + deltaY;
    }
    else if (n >= 5)
    {

        int sumOfXChanges = ((positions[n - 1].x - positions[n - 2].x) * 4) +
                            ((positions[n - 2].x - positions[n - 3].x) * 3) +
                            ((positions[n - 3].x - positions[n - 4].x) * 2) +
                            ((positions[n - 4].x - positions[n - 5].x) * 1);

        int sumOfYChanges = ((positions[n - 1].y - positions[n - 2].y) * 4) +
                            ((positions[n - 2].y - positions[n - 3].y) * 3) +
                            ((positions[n - 3].y - positions[n - 4].y) * 2) +
                            ((positions[n - 4].y - positions[n - 5].y) * 1);

        int deltaX = (int)std::round((float)sumOfXChanges / 10.0);
        int deltaY = (int)std::round((float)sumOfYChanges / 10.0);

        predicted_next_pos.x = positions.back().x + deltaX;
        predicted_next_pos.y = positions.back().y + deltaY;
    }
}



            