#define OLC_PGE_APPLICATION

#include <iostream>
#include <string>
#include <algorithm>

#include "olcPixelGameEngine.h"

class Asteroids : public olc::PixelGameEngine
{
public:
	Asteroids()
	{
		sAppName = "Asteroids";
	}

private:
	struct sSpaceObject
	{
		float x;
		float y;
		float dx;
		float dy;
		int nSize;
		float angle;
	};

	std::vector<sSpaceObject> vecAsteroids;
	std::vector<sSpaceObject> vecBullets;
	sSpaceObject ship;
	bool is_ship_dead = false;
	int Score = 0;

	// ship models
	std::vector<std::pair<float, float>> model_ship, model_ship_nothrust, model_ship_thrust;
	// asteroid model
	std::vector<std::pair<float, float>> model_asteroid;

protected:
	// Initialization
	bool OnUserCreate() override
	{

		// Static resources

		// ship models
		model_ship_nothrust = {
			{0.0f, -4.0f},
			{-2.5f, 3.5f},
			{-2.0f, 2.0f},
			{2.0f, 2.0f},
			{2.5f, 3.5f}};
		model_ship_thrust = {
			{0.0f, -4.0f},
			{-2.5f, 3.5f},
			{-2.0f, 2.0f},
			{1.0f, 2.0f},
			{0.0f, 6.0f},
			{-1.0f, 2.0f},
			{2.0f, 2.0f},
			{2.5f, 3.5f}};

		// asteroids model
		int Nvertices = 20;
		for (int i = 0; i < Nvertices; i++)
		{
			// float radius = 1.0f; // unit circle, nSize is the radius
			//  random radius 0.8 - 1.2
			float radius = (float)rand() / (float)RAND_MAX * 0.4f + 0.8f;

			float angle = (float)i / (float)Nvertices * 2 * 3.14159f;
			model_asteroid.push_back(std::make_pair(radius * sinf(angle),
													radius * cosf(angle)));
		}
		ResetGame(0);

		return true;
	}

	// Main game loop
	bool OnUserUpdate(float fElapsedTime) override
	{
		// if ship died restart game
		if (is_ship_dead)
			ResetGame(0);

		// Clear Screen
		Clear(olc::BLACK);

		// Steer ship
		if (GetKey(olc::Key::LEFT).bHeld)
			ship.angle -= 2.0f * fElapsedTime;

		if (GetKey(olc::Key::RIGHT).bHeld)
			ship.angle += 2.0f * fElapsedTime;

		// Thrust
		if (GetKey(olc::Key::UP).bHeld)
		{
			// Thrust creates Acceleration which changes velocity
			ship.dx += sin(ship.angle) * 20.0f * fElapsedTime;
			ship.dy += -cos(ship.angle) * 20.0f * fElapsedTime;
			model_ship = model_ship_thrust;
		}
		else
			model_ship = model_ship_nothrust;

		// update ship position
		ship.x += ship.dx * fElapsedTime;
		ship.y += ship.dy * fElapsedTime;

		// keep ship in gamespace
		WrapCoordinates(ship.x, ship.y, ship.x, ship.y);

		// check for collision with asteroids

		for (auto &a : vecAsteroids)
		{
			if (IsPointInsideCircle(a.x, a.y, a.nSize + ship.nSize, ship.x, ship.y))
				is_ship_dead = true;
		}

		// fire bullets
		if (GetKey(olc::Key::SPACE).bReleased)
			vecBullets.push_back({ship.x, ship.y,
								  ship.dx + 100.0f * sinf(ship.angle),
								  ship.dy - 100.0f * cosf(ship.angle),
								  0, 0});

		// temp vector to create new asteroids  without
		// disrupting vecAsteroids while iterating through it
		std::vector<sSpaceObject> newAsteroids;

		// update and draw bullets
		for (auto &b : vecBullets)
		{
			b.x += b.dx * fElapsedTime;
			b.y += b.dy * fElapsedTime;
			WrapCoordinates(b.x, b.y, b.x, b.y);

			// Draw bullet
			Draw(b.x, b.y, olc::YELLOW);

			// Check collision with asteroids
			for (auto &a : vecAsteroids)
			{

				if (IsPointInsideCircle(a.x, a.y, a.nSize, b.x, b.y))
				{
					// if nSize>4 split asteroid in 2 of half size
					if (a.nSize > 4)
					{
						// split at two randon angles 0-2PI
						float angle1(((float)rand() / (float)RAND_MAX) * 2 * 3.14159f);
						float angle2(((float)rand() / (float)RAND_MAX) * 2 * 3.14159f);
						newAsteroids.push_back({a.x, a.y,
												a.dx + 20.0f * sinf(angle1),
												a.dy + 20.0f * cosf(angle1),
												(int)a.nSize >> 1, // bitshifted to divide it by 2))
												a.angle + 3.14159f / 3});
						newAsteroids.push_back({a.x, a.y,
												a.dx + 20.0f * sinf(angle2),
												a.dy + 20.0f * cosf(angle2),
												(int)a.nSize >> 1, // bitshifted to divide it by 2))
												a.angle - 3.14159f / 4});
					}
					// Destroy Asteroid
					// to avoid modifying the vector while iterating it:
					// move asteroid off-screen so it is later cleaned up
					a.x = -100;
					// increase Score
					Score += 100;

					// Destroy bullet
					// to avoid modifying the vector while scanning it:
					// move the bullet off-screen and it will
					// be cleaned up later
					b.x = -100;
				}
			}
		}

		// Append newly created asteroids to asteroids vector
		for (auto a : newAsteroids)
		{
			vecAsteroids.push_back(a);
		}

		// Remove off-screen bullets
		if (vecBullets.size() > 0)
		{
			auto i = remove_if(vecBullets.begin(), vecBullets.end(), [&](sSpaceObject o)
							   { return (o.x < 1 || o.y < 1 || o.x >= ScreenWidth() - 1 || o.y >= ScreenHeight() - 1); });
			if (i != vecBullets.end())
				vecBullets.erase(i);
		}

		// Remove off-screen asteroids
		if (vecAsteroids.size() > 0)
		{
			auto i = remove_if(vecAsteroids.begin(), vecAsteroids.end(), [&](sSpaceObject o)
							   { return (o.x < 0); }); // only check x<100, asteroids only go of screen when sent making x=-100
			if (i != vecAsteroids.end())
				vecAsteroids.erase(i);
		}

		if (vecAsteroids.empty())
		{
			// all asteroids destroyed
			ResetGame(1000);
		}

		// Draw ship
		DrawWireFrameModel(model_ship,
						   ship.x, ship.y, ship.angle,
						   (float)ship.nSize, olc::CYAN);

		// Draw Score
		std::string str = "SCORE: " + std::to_string(Score);
		DrawString(2, 2, str);

		// update and draw asteroids
		for (auto &a : vecAsteroids)
		{
			a.x += a.dx * fElapsedTime;
			a.y += a.dy * fElapsedTime;
			WrapCoordinates(a.x, a.y, a.x, a.y);
			a.angle += 0.0001f * 16.0f / (float)a.nSize;

			// Draw asteroid
			DrawWireFrameModel(model_asteroid,
							   a.x, a.y, a.angle,
							   a.nSize, olc::YELLOW);
		}

		return true;
	}

	void WrapCoordinates(float input_x, float input_y,
						 float &output_x, float &output_y)
	{
		output_x = input_x;
		output_y = input_y;
		if (input_x < 0.0f)
			output_x = input_x + (float)ScreenWidth();
		if (input_x > (float)ScreenWidth())
			output_x = input_x - (float)ScreenWidth();

		if (input_y < 0.0f)
			output_y = input_y + (float)ScreenHeight();
		if (input_y > (float)ScreenHeight())
			output_y = input_y - (float)ScreenHeight();
	}

	bool Draw(int x, int y, olc::Pixel col = olc::WHITE) override
	{
		float fx, fy;
		WrapCoordinates(x, y, fx, fy);
		return olc::PixelGameEngine::Draw(fx, fy, col);
	}

	void DrawWireFrameModel(const std::vector<std::pair<float, float>> &model,
							float x, float y,
							float angle = 0.0f,
							float scale = 1.0f,
							olc::Pixel color = olc::WHITE)
	{

		// pair.first = x coordinate
		// pair.second = y coordinate

		int N = model.size();

		std::vector<std::pair<float, float>> transformed;
		// transformed.resize(N);

		// Rotate
		for (int i = 0; i < N; i++)
		{
			float x, y;
			x = model[i].first * cosf(angle) -
				model[i].second * sinf(angle);
			y = model[i].first * sinf(angle) +
				model[i].second * cosf(angle);
			transformed.push_back({x, y});
		}

		// Scale
		for (int i = 0; i < N; i++)
		{
			transformed[i].first *= scale;
			transformed[i].second *= scale;
		}

		// Translate
		for (int i = 0; i < N; i++)
		{
			transformed[i].first += x;
			transformed[i].second += y;
		}

		// Draw closed polygon
		for (int i = 0; i < N + 1; i++)
		{
			int j = i + 1;
			DrawLine(transformed[i % N].first,
					 transformed[i % N].second,
					 transformed[j % N].first,
					 transformed[j % N].second,
					 color);
		}
	}

	bool IsPointInsideCircle(float cx, float cy, float radius, float x, float y)
	{
		return sqrt((x - cx) * (x - cx) + (y - cy) * (y - cy)) < radius;
	}

	void ResetGame(int score_reset = 0)
	{
		if (score_reset == 0)
		{
			// initialize score and ship position
			Score = 0;

			ship.x = ScreenWidth() / 2.0f;
			ship.y = ScreenHeight() / 2.0f;
			ship.dx = 0.0f;
			ship.dy = 0.0f;
			ship.nSize = 2;
			ship.angle = 0.0f;
		}
		else
		{ // cleared level: keep ship position and reward
			Score += score_reset;
		}

		// clear vectors
		vecAsteroids.clear();
		vecBullets.clear();

		// create 3 asteroids out of the way

		vecAsteroids.push_back({ship.x + 80.0f * sinf(ship.angle + 3.14159f / 3.0f),
								ship.y + 80.0f * cosf(ship.angle + 3.14159f / 3.0f),
								ship.dx + 25.0f * cosf(ship.angle - 3.14159f / 3.0f),
								ship.dy + 25.0f * sinf(ship.angle - 3.14159f / 3.0f),
								(int)16,
								-3.14159f / 6.0f});

		vecAsteroids.push_back({ship.x + 80.0f * sinf(ship.angle - 3.14159f / 2.0f),
								ship.y + 80.0f * cosf(ship.angle - 3.14159f / 2.0f),
								ship.dx + 20.0f * cosf(ship.angle + 3.14159f / 4.0f),
								ship.dy + 20.0f * sinf(ship.angle + 3.14159f / 4.0f),
								(int)16,
								3.14159f / 4.0f});

		vecAsteroids.push_back({ship.x + 100.0f * sinf(ship.angle - 3.14159f / 3.0f),
								ship.y + 100.0f * cosf(ship.angle - 3.14159f / 3.0f),
								ship.dx + 30.0f * cosf(ship.angle + 3.14159f ),
								ship.dy + 30.0f * sinf(ship.angle + 3.14159f ),
								(int)16,
								3.14159f});

		// make ship alive
		is_ship_dead = false;
	};
};

int main()
{
	Asteroids game;
	if (game.Construct(275, 150, 8, 8))
		game.Start();
	return 0;
}
