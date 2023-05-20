
#define TELLO_DEBUG // This can be used to enable verbose logging
#include "tello.hpp"
#include <iostream>
#include <opencv2/opencv.hpp>

void demo_fly()
{

    Tello tello;
    if (!tello.connect())
    {
        return;
    }

    PRINTF_WARN("Tello is connected and about to take off and fly around! Are you ready? [Press Enter]");
    std::cin.get();

    tello.takeoff();

    tello.sleep(500);     // wait 500ms
    tello.turn_right(90); // turn 90 degrees right
    tello.sleep(500);
    tello.turn_left(90); // turn 90 degrees left
    tello.sleep(500);

    tello.land();
}

void demo_cam()
{

    Tello tello;
    if (!tello.connect())
    {
        return;
    }

    tello.enable_video_stream();
    cv::VideoCapture capture{"udp://0.0.0.0:11111", cv::CAP_FFMPEG};

    while (true)
    {
        cv::Mat frame;
        capture >> frame;
        if (!frame.empty())
        {
            cv::imshow("Tello Stream | ESC to exit", frame);
        }
        if (cv::waitKey(1) == 27)
        {
            tello.disable_video_stream();
            cv::destroyAllWindows();
            return;
        }
    }
}
void demo_key()
{
    Tello tello;
    if (!tello.connect())
    {
        return;
    }

    int MOVE_UP = 113;    // q
    int MOVE_DOWN = 97;   // a
    int TURN_LEFT = 111;  // o
    int TURN_RIGHT = 112; // p
    int LAND = 27;        // ESC
    int TAKE_OFF = 32;    // SPACE
    double TSPEED_INC = 10.0;
    double RSPEED_INC = 10.0;
    double MAX_SPEED = 20.0;

    PRINTF("SPACE - take off");
    PRINTF("q - move up");
    PRINTF("a - move down");
    PRINTF("o - rotate left");
    PRINTF("p - rotate right");
    PRINTF("ESC - land");
    PRINTF_WARN("Tello is connected and about to take off and fly around [Press SPACE]");

    int keypress = -1;
    cv::Mat frame(cv::Size(640, 480), CV_8UC3, cv::Scalar(0.0, 0.0, 0.0));
    cv::imshow("Put this window in focus for commands to work", frame);

    while (keypress != TAKE_OFF)
    {
        keypress = cv::waitKey(33) & 255; // 255 is a mask to ignore modifier keys
    }
    std::cout << "Taking off" << std::endl;
    //tello.takeoff();
    
    double left_right, up_down;
    while (true)
    {
        up_down = 0;
        left_right = 0;

        if (keypress == LAND)
            break;
        
        if (keypress == MOVE_UP) // && up_down < (MAX_SPEED - TSPEED_INC))
            up_down = TSPEED_INC; // move up TSPEED_INC cm
        else if (keypress == MOVE_DOWN) // && up_down > -(MAX_SPEED - TSPEED_INC))
            up_down = -TSPEED_INC; // move down TSPEED_INC cm
        
        if (keypress == TURN_RIGHT) // && left_right < (MAX_SPEED - TSPEED_INC))
            left_right = RSPEED_INC; // rotate right RSPEED_INC degrees
        else if (keypress == TURN_LEFT) //  && left_right > -(MAX_SPEED - TSPEED_INC))
            left_right = -RSPEED_INC; // rotate left RSPEED_INC degrees
        
        std::cout << "Sending command: rc " << left_right << " 0.0 " << up_down << " 0.0" << std::endl;
        //tello.move(left_right, 0.0, up_down, 0.0);
        tello.sleep(20);
        keypress = cv::waitKey(33);
    }
    std::cout << "Landing" << std::endl;
    tello.land();
}

int main()
{
    while (true)
    {
        system("clear");
        PRINTF_INFO("1. Demo take off and landing");
        PRINTF_INFO("2. Demo streaming camera");
        PRINTF_INFO("3. Demo keypad control");
        PRINTF_INFO("4. Quit");
        PRINTF_INFO("Select option [1-4]");
        char a = std::cin.get();
        if (a == '1')
        {
            demo_fly();
            continue;
        }
        if (a == '2')
        {
            demo_cam();
            continue;
        }
        if (a == '3')
        {
            demo_key();
            continue;
        }
        if (a == '4')
            break;
    }

    PRINTF_INFO("Bye!");
    return 0;
}
