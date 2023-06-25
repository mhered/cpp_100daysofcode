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

    // Blocks
    olc::vi2d vBlockSize = {16, 16}; // 2d vector size in pixels of one tile: 16x16 pixels"
    std::unique_ptr<int[]> blocks;   // pointer to array of integers

    // screen
    int HEIGHT = 19;
    int WIDTH = 26;

    // Bat
    olc::vf2d vBatPos = {1.0f, float(HEIGHT - 2)};
    float fBatWidth = 4.0f;
    float fBatHeight = 1.0f;
    float fBatSpeed = 50.0f;

    // Ball
    olc::vf2d vBallPos = {0.0f, 0.0f};
    olc::vf2d vBallDir = {0.0f, 0.0f};
    float fBallSpeed = 18.0f;
    float fBallRadius = 5.0f;

    std::unique_ptr<olc::Sprite> sprTile; // Sprite tile

public:
    bool OnUserCreate() override
    {
        // Called once at the start

        blocks = std::make_unique<int[]>(HEIGHT * WIDTH);

        for (int y = 0; y < HEIGHT; y++)
        {
            for (int x = 0; x < WIDTH; x++)
            {
                if (x == 0 || y == 0 || x == WIDTH - 1)
                    blocks[y * WIDTH + x] = 10;
                else
                    blocks[y * WIDTH + x] = 0;

                // Level 1 here is hard coded
                // think about storing different layouts in a file
                // e.g. as strings, and reading them in

                if (x > 2 && x <= WIDTH - 4 && y > 2 && y <= 3) // 2 rows red
                    blocks[y * WIDTH + x] = 1;
                if (x > 2 && x <= WIDTH - 4 && y > 4 && y <= 5) // 2 rows orange
                    blocks[y * WIDTH + x] = 2;
                if (x > 2 && x <= WIDTH - 4 && y > 6 && y <= 7) // 2 rows yellow
                    blocks[y * WIDTH + x] = 3;
            }
        }

        // Load the sprite
        sprTile = std::make_unique<olc::Sprite>("./assets/tut_tiles.png");

        // Start Ball
        float fAngle = float(rand()) / float(RAND_MAX) * 2.0f * 3.14159f;
        fAngle = -0.4f;
        vBallDir = {cos(fAngle), sin(fAngle)};
        vBallPos = {12.5f, 15.5f};

        return true;
    }

    bool OnUserUpdate(float fElapsedTime) override
    {
        // called once per frame
        // fElapsedTime represents the previous frame duration in seconds
        // allows working in pseudo-real-time

        // A better collision detection
        // Calculate where ball should be, if no collision
        olc::vf2d vPotentialBallPos = vBallPos + vBallDir * fBallSpeed * fElapsedTime;

        // Test for hits 4 points around ball
        olc::vf2d vTileBallRadialDims = {fBallRadius / vBlockSize.x, fBallRadius / vBlockSize.y};

        auto TestResolveCollisionPoint = [&](const olc::vf2d &point)
        {
            olc::vi2d vTestPoint = vPotentialBallPos + vTileBallRadialDims * point;

            auto &tile = blocks[vTestPoint.y * WIDTH + vTestPoint.x];
            if (tile == 0)
            {
                // Do Nothing, no collision
                return false;
            }
            else
            {
                // Ball has collided with a tile
                bool bTileHit = tile < 10;
                if (bTileHit)
                    tile--;

                // Collision response
                if (point.x == 0.0f)
                    vBallDir.y *= -1.0f;
                if (point.y == 0.0f)
                    vBallDir.x *= -1.0f;
                return bTileHit;
            }
        };

        bool bHasHitTile = false;
        bHasHitTile |= TestResolveCollisionPoint(olc::vf2d(0, -1));
        bHasHitTile |= TestResolveCollisionPoint(olc::vf2d(0, +1));
        bHasHitTile |= TestResolveCollisionPoint(olc::vf2d(-1, 0));
        bHasHitTile |= TestResolveCollisionPoint(olc::vf2d(+1, 0));

        // Actually update ball position with modified direction
        vBallPos += vBallDir * fBallSpeed * fElapsedTime;

        // Refresh Display

        // Erase previous frame
        Clear(olc::VERY_DARK_GREY);

        // Draw Screen
        SetPixelMode(olc::Pixel::MASK); // Dont draw pixels which have any transparency
        for (int y = 0; y < HEIGHT; y++)
        {
            for (int x = 0; x < WIDTH; x++)
            {
                switch (blocks[y * WIDTH + x])
                {
                case 0: // Do nothing
                    break;
                case 10: // Draw Boundary: Gray
                    DrawPartialSprite(olc::vi2d(x, y) * vBlockSize,
                                      sprTile.get(), olc::vi2d(0, 0) * vBlockSize, vBlockSize);
                    break;
                case 1: // Draw Damaged Block: Red
                    DrawPartialSprite(olc::vi2d(x, y) * vBlockSize,
                                      sprTile.get(), olc::vi2d(1, 0) * vBlockSize, vBlockSize);
                    break;
                case 2: // Draw Hit Block: Orange
                    DrawPartialSprite(olc::vi2d(x, y) * vBlockSize,
                                      sprTile.get(), olc::vi2d(2, 0) * vBlockSize, vBlockSize);
                    break;
                case 3: // Draw New Block: Yellow
                    DrawPartialSprite(olc::vi2d(x, y) * vBlockSize,
                                      sprTile.get(), olc::vi2d(3, 0) * vBlockSize, vBlockSize);
                    break;
                }
            }
        }

        SetPixelMode(olc::Pixel::NORMAL); // Back to normal when finished

        // Handle User Input
        if (GetKey(olc::Key::LEFT).bHeld)
            vBatPos.x -= fBatSpeed * fElapsedTime;
        if (GetKey(olc::Key::RIGHT).bHeld)
            vBatPos.x += fBatSpeed * fElapsedTime;

        if (vBatPos.x < 1.0f)
            vBatPos.x = 1.0f;
        if (vBatPos.x + fBatWidth > float(WIDTH - 1))
            vBatPos.x = float(WIDTH - 1) - fBatWidth;

        // Check if Ball hits Bat
        if ((vBallPos.y >= (vBatPos.y - vTileBallRadialDims.y)) && (vBallPos.x > vBatPos.x) && (vBallPos.x < (vBatPos.x + fBatWidth)))
            vBallDir.y *= -1.0f;

        // Check if ball has gone off screen
        if (vBallPos.y >= HEIGHT - 1)
        {
            // Reset ball location
            vBallPos = {WIDTH / 2.0f, HEIGHT / 2.0f};
            // Choose Random direction
            float fAngle = (float(rand()) / float(RAND_MAX)) * 2.0f * 3.14159f;
            vBallDir = {cos(fAngle), sin(fAngle)};
        }

        // Draw Bat
        FillRect(int(vBatPos.x * vBlockSize.x),
                 int(vBatPos.y * vBlockSize.y),
                 int(fBatWidth * vBlockSize.x),
                 int(fBatHeight * vBlockSize.y),
                 olc::WHITE);

        // Draw Ball
        FillCircle(vBallPos * vBlockSize, fBallRadius, olc::CYAN);

        // debug
        std::cout << "Bat x: " << vBatPos.x << " y: " << vBatPos.y;
        std::cout << " | Ball x: " << vBallPos.x << " y: " << vBallPos.y << std::endl;

        return true;
    }
};

int main()
{
    Arkanoid demo;
    if (demo.Construct(550, 300, 2, 2))
        demo.Start();

    return 0;
}