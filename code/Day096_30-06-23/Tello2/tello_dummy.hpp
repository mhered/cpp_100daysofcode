// placeholder to simulate tello.hpp
// to use during development without the Tello

#include <iostream>
#include <chrono>
#include <sstream>

#define PRINTF(msg) std::cout << msg << std::endl;
#define PRINTF_WARN(msg) std::cout << "WARNING: " << msg << std::endl;

class Tello
{
public:
    Tello()
    {
    }

    ~Tello()
    {
    }

    bool connect()
    {
        PRINTF("Tello is Connecting...");
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        PRINTF("Tello is Connected!");
        return true;
    };
    void takeoff()
    {
        PRINTF("Tello is Taking off...");
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    };

    void land()
    {
        PRINTF("Tello is Landing...");
        std::this_thread::sleep_for(std::chrono::milliseconds(2000));
        PRINTF("Tello has Landed!");
    };

    void sleep(double secs)
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(int(secs * 1000)));
    };

    void move(double lr, double fb, double ud, double yaw)
    {
        std::stringstream ss;
        ss << "Sending command: rc " << lr
           << " " << fb
           << " " << ud
           << " " << yaw;
        PRINTF(ss.str());
        //std::this_thread::sleep_for(std::chrono::milliseconds(100));
    };
};