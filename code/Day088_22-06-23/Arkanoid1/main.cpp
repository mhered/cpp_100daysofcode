#define OLC_PGE_APPLICATION
#include "olcPixelGameEngine.h"

class Arkanoid : public olc::PixelGameEngine
{
public:
    Arkanoid()
    {
        sAppName = "Arkanoid";
    }

private:
    // General constants
    const int MARGIN = 10;

    // bat
    float fBatPos = 20.0f;
    float fBatWidth = 40.0f;
    float fBatHeight = 10.0f;
    float fBatSpeed = 100.0f;

    // ball
    olc::vf2d vBall = {200.0f, 200.0f};
    float fBallRadius = 5.0f;
    olc::vf2d vBallVel = { 200.0f, -100.0f }; // initial velocity

public:
    bool OnUserCreate() override
    {
        // Called once at the start
        return true;
    }

    bool OnUserUpdate(float fElapsedTime) override
    {
        // called once per frame
        // fElapsedTime represents the previous frame duration in seconds
        // allows working in pseudo-real-time

        // Erase previous frame
        Clear(olc::DARK_GREY);

        // Draw Boundary
        DrawLine(MARGIN, MARGIN, ScreenWidth() - MARGIN, MARGIN, olc::WHITE);
        DrawLine(MARGIN, MARGIN, MARGIN, ScreenHeight() - MARGIN, olc::WHITE);
        DrawLine(ScreenWidth() - MARGIN, MARGIN, ScreenWidth() - MARGIN, ScreenHeight() - MARGIN, olc::WHITE);

        // Handle User Input
        if (GetKey(olc::Key::LEFT).bHeld)
            fBatPos -= fBatSpeed * fElapsedTime;
        if (GetKey(olc::Key::RIGHT).bHeld)
            fBatPos += fBatSpeed * fElapsedTime;

        if (fBatPos < MARGIN + fBatSpeed * fElapsedTime)
            fBatPos = MARGIN + fBatSpeed * fElapsedTime;
        if (fBatPos + fBatWidth > float(ScreenWidth()) - MARGIN)
            fBatPos = float(ScreenWidth()) - MARGIN - fBatWidth;

        /*
        // Controlling the Ball position with the Mouse
        if (GetMouse(0).bHeld)
        {
            vBall = {float(GetMouseX()), float(GetMouseY())};
        }
        // Controlling the Ball size with the Mouse
        if (GetMouseWheel() > 0)
            fBallRadius += 1.0f;
        if (GetMouseWheel() < 0)
            fBallRadius -= 1.0f;
        if (fBallRadius < 5.0f)
            fBallRadius = 5.0f;*/

        // Update Ball
        vBall += vBallVel * fElapsedTime;

        // Really crude arena detection - this approach sucks
        if (vBall.y <= 10.0f)
            vBallVel.y *= -1.0f;
        if (vBall.x <= 10.0f)
            vBallVel.x *= -1.0f;
        if (vBall.x >= float(ScreenWidth()) - 10.0f)
            vBallVel.x *= -1.0f;

        // Check Bat
        if (vBall.y >= (float(ScreenHeight()) - 20.0f) && (vBall.x > fBatPos) && (vBall.x < fBatPos + fBatWidth))
            vBallVel.y *= -1.0f;

        // Check if ball has gone off screen
        if (vBall.y > ScreenHeight())
        {
            // Reset ball location
            vBall = {200.0f, 200.0f};
            // Choose Random direction
            float fAngle = (float(rand()) / float(RAND_MAX)) * 2.0f * 3.14159f;
            vBallVel = {300.0f * cos(fAngle), 300.0f * sin(fAngle)};
        }

        // Draw Bat
        FillRect(int(fBatPos), ScreenHeight() - 2 * MARGIN, int(fBatWidth), int(fBatHeight), olc::WHITE);

        // Draw Ball
        FillCircle(vBall, fBallRadius, olc::YELLOW);

        return true;
    }
};

int main()
{
    Arkanoid demo;
    if (demo.Construct(256, 240, 2, 2))
        demo.Start();

    return 0;
}