#include "shapes.h"

////////Auxiliary//////////
///////////////////////////

double distance(double x1, double y1, double x2, double y2)
{
    return sqrt(pow(x1 - x2, 2) + pow(y1 - y2, 2));
}

// true if point inside polygon
bool polygonPoint(std::vector<cv::Point> vertices, double px, double py)
{
    bool collision = false;

    // go through each of the vertices, plus the next
    // vertex in the list

    int next = 0;
    for (int current = 0; current < vertices.size(); current++)
    {

        // get next vertex in list
        // if we've hit the end, wrap around to 0
        next = current + 1;
        if (next == vertices.size())
            next = 0;

        // get the PVectors at our current position
        // this makes our if statement a little cleaner
        cv::Point vc = vertices[current]; // c for "current"
        cv::Point vn = vertices[next];    // n for "next"

        // compare position, flip 'collision' variable
        // back and forth
        if (((vc.y > py && vn.y < py) || (vc.y < py && vn.y > py)) &&
            (px < (vn.x - vc.x) * (py - vc.y) / (vn.y - vc.y) + vc.x))
        {
            collision = !collision;
        }
    }
    return collision;
}

////////Segment////////////
///////////////////////////

bool Segment::is_pt_on_segment(double x, double y)
{
    return distance(x, y, x1, y1) + distance(x, y, x2, y2) - distance(x1, y1, x2, y2) < Segment::TOL;
};

void Segment::draw(cv::Mat &img, cv::Scalar color)
{
    // draw segment in color provided
    cv::Point pt1((int)x1, (int)y1);
    cv::Point pt2((int)x2, (int)y2);
    std::vector<cv::Point> corners = {pt1, pt2};
    cv::polylines(img, corners, false, color, 2);
}


////////Circle/////////////
///////////////////////////

bool Circle::collides_with(Circle other)
{
    double dist = distance(centre_x, centre_y, other.centre_x, other.centre_y);
    if (dist <= radius + other.radius + Circle::TOL)
    {
        return true;
    }
    return false;
}

bool Circle::collides_with(Segment other)
{
    // check if extremes inside circle
    double dist1 = distance(centre_x, centre_y, other.x1, other.y1);
    if (dist1 <= radius + Circle::TOL)
    {
        return true;
    }
    double dist2 = distance(centre_x, centre_y, other.x2, other.y2);
    if (dist2 <= radius + Circle::TOL)
    {
        return true;
    }

    // get closest point on the line
    double length = distance(other.x1, other.y1, other.x2, other.y2);
    double dot = (((centre_x - other.x1) * (other.x2 - other.x1)) +
                  ((centre_y - other.y1) * (other.y2 - other.y1))) /
                 pow(length, 2);

    double closest_x = other.x1 + (dot * (other.x2 - other.x1));
    double closest_y = other.y1 + (dot * (other.y2 - other.y1));
    // check if the closest point on the line falls inside the segment
    // and distance from line to circle is less than radius
    if (other.is_pt_on_segment(closest_x, closest_y) &&
        distance(centre_x, centre_y, closest_x, closest_y) <= radius)
        return true;

    return false;
}

void Circle::draw(cv::Mat &img, cv::Scalar color)
{
    // draw circle in color provided
    cv::circle(img, cv::Point(centre_x, centre_y), radius, color, 2);
}

////////Rectangle//////////
///////////////////////////

std::vector<cv::Point> Rectangle::vertices()
{
    std::vector<cv::Point> vertices;
    // rotate by angle (deg) and then translate to x_centre, y_centre
    double angle_rad = CV_PI / 180 * angle_deg;
    for (int i = 0; i < primitive.size(); i++)
    {
        double xx, yy;
        xx = primitive[i].x * cos(angle_rad) - primitive[i].y * sin(angle_rad);
        yy = primitive[i].x * sin(angle_rad) + primitive[i].y * cos(angle_rad);
        vertices.push_back({(int)(xx + centre_x), (int)(yy + centre_y)});
    }
    return vertices;
}

bool Rectangle::collides_with(Circle other)
{
    std::vector<cv::Point> corners = vertices();
    // check corners
    cv::Point corner1 = corners[corners.size() - 1];
    for (auto corner2 : corners)
    {
        // check side
        if (other.collides_with(Segment(corner1, corner2)))
            return true;

        // prepare next side
        corner1 = corner2;
    }

    if (polygonPoint(corners, other.centre_x, other.centre_y))
        return true;

    return false;
}

// NOT IMPLEMENTED
bool Rectangle::collides_with(Rectangle other)
{
    /*double dist = sqrt(pow(x - other.x, 2) + pow(y - other.y, 2));
    if (dist <= radius + other.radius + Circle::TOL)
    {
        return true;
    }*/
    return false;
}

void Rectangle::draw(cv::Mat &img, cv::Scalar color)
{
    // draw rectangle in color provided
    cv::polylines(img, vertices(), true, color, 2);
}