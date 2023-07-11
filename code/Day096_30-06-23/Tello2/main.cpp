#include "tello.hpp"

#define OLC_PGE_APPLICATION
#include "olcPixelGameEngine.h"


class Example : public olc::PixelGameEngine
{
public:
    Example()
    {
        sAppName = "Tello";
    }
    // Called once at the start, so create things here
    double TSPEED_INC = 5.0;
    double RSPEED_INC = 5.0;
    double MAX_SPEED = 20.0;

    Tello tello;

    double left_right = 0;
    double up_down = 0;
    bool on_ground = true;

public:
    bool OnUserCreate() override
    {

        PRINTF("SPACE - take off");
        PRINTF("UP - move up");
        PRINTF("DOWN - move down");
        PRINTF("LEFT - rotate left");
        PRINTF("RIGHT - rotate right");
        PRINTF("ESCAPE - land");

        if (!tello.connect())
        {
            return false;
        }
        PRINTF_WARN("Tello is connected and about to take off and fly around [Press SPACE]");
        return true;
    }

    bool OnUserDestroy() override
    {
        // Called once at the end, so clean up
        return true;
    }

    bool OnUserUpdate(float fElapsedTime) override
    {
        // called once per frame
        Clear(olc::BLACK);

        if (on_ground)
            if (GetKey(olc::Key::SPACE).bReleased)
            {
                tello.takeoff();
                on_ground = false;
            }
            else
                return true;

        if (GetKey(olc::Key::ESCAPE).bReleased)
        {
            tello.land(); // then end program!
            on_ground = true;
            up_down = 0;
            left_right = 0;
            return false;
        }

        if (GetKey(olc::Key::UP).bHeld)
        {
            up_down += TSPEED_INC; // move up TSPEED_INC cm
            up_down = up_down > MAX_SPEED ? MAX_SPEED : up_down;
        }
        else if (GetKey(olc::Key::DOWN).bHeld)
        {
            up_down -= TSPEED_INC; // move up TSPEED_INC cm
            up_down = up_down < -MAX_SPEED ? -MAX_SPEED : up_down;
        }
        else
        {
            if (up_down >= TSPEED_INC)
                up_down -= TSPEED_INC;
            if (up_down <= -TSPEED_INC)
                up_down += TSPEED_INC;
        }

        if (GetKey(olc::Key::RIGHT).bHeld)
        {
            left_right += RSPEED_INC; // rotate right RSPEED_INC degrees
            left_right = left_right > MAX_SPEED ? MAX_SPEED : left_right;
        }
        else if (GetKey(olc::Key::LEFT).bHeld)
        {
            left_right -= RSPEED_INC; // rotate left RSPEED_INC degrees
            left_right = left_right < -MAX_SPEED ? -MAX_SPEED : left_right;
        }
        else
        {
            if (left_right >= RSPEED_INC)
                left_right -= RSPEED_INC;
            if (left_right <= -RSPEED_INC)
                left_right += RSPEED_INC;
        }

        tello.move(left_right, 0.0, up_down, 0.0);
        tello.sleep(100);
        return true;
    }
};

int main()
{
    Example demo;
    if (demo.Construct(160, 100, 8, 8))
        demo.Start();

    return 0;
}

void demo_key()
{
}
