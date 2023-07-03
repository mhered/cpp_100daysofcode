#link: https://github.com/herrnamenlos123/tello

# Tello 2

Some time ago I left the project [Tello](https://github.com/mhered/cpp_100daysofcode/blob/main/code/Day053_18-05-23/Tello) unfinished because I was struggling to get the keyboard input in function `demo_key()` to work properly. It is time now to apply the learnings from projects  [KeyboardGameControl](https://github.com/mhered/cpp_100daysofcode/blob/main/code/Day086_20-06-23/KeyboardGameControl) and more importantly [Asteroids](https://github.com/mhered/cpp_100daysofcode/blob/main/code/Day090_24-06-23/Asteroids) and complete that challenge.


## Backgroud

As a reminder the goal was to replicate using C++ at least some of the projects I did two years ago with my Tello drone using python: https://github.com/mhered/tello-fun.

I decided to try out [tello](https://github.com/herrnamenlos123/tello), a C++14 single-header library to control the Tello, last updated in Nov22. Note it uses SDK 2.0, which apparently may be not fully compatible with the "normal" Tello. 

## Getting started

1. Download `tello.hpp` from https://github.com/mcx/tello/tree/master on to the project folder
2. Download the example `main.cpp` from https://github.com/mcx/tello/tree/master/example/src/
3. Note: compiling failed with message `usr/include/c++/9/thread:126: undefined reference to 'pthread_create'`. I fixed it adding `"-lpthread"` to `"args":` in `tasks.json`, see here: https://stackoverflow.com/questions/1662909/undefined-reference-to-pthread-create-in-linux

Note: to connect the Tello drone to the laptop:
1. Switch on the Tello drone pressing the side button
2. Connect the laptop to `TELLO-EFD008` WIFI network and wait for a blinking yellow LED in the Tello drone

## The task

* `void demo_key()` - implement basic control for the Tello with the laptop keyboard: take off, move up/down, rotate left/right and land. 

I conducted some troubleshooting to try to identify the root cause of the unresponsive behaviour of the Tello in the previous implementation, including:
* adjust time waiting for `wayKey()` -> reduced from 100ms to 33ms
* `STEP` at 10% too high -> reduced from 10% to 2%
* max speed too high -> reduced from 100% to 20% 
* update firmware: see here how to force update: https://forum.dji.com/thread-275710-1-1.html -> updated to 01.04.91.01
* bad lighting, Need for calibration? (see https://github.com/damiafuentes/DJITelloPy/issues/37#issuecomment-679454623 for common sources of issues) -> calibrated following instructions in the app, requires removing propellers and guards

None of the above seemed to work so I suspected the problem lay with the keyboard input routines. So I set out to write proper ones like those implememnted by `olcPixelGameEngine.h` see project [Asteroids](https://github.com/mhered/cpp_100daysofcode/blob/main/code/Day090_24-06-23/Asteroids)

Note: toay I didnt have with me the Tello dron so I wrote a dummy header library `dummy_tello.hpp` to test the keyboard input routines. I simply mimics the members of Tello class and simulates some delays.

The result is promising. Tomorrow we will see if the drone works for real!

## Other C++ Tello resources worth exploring

For ROS2 integration, at some later point, I may explore [tello_ros](https://github.com/clydemcqueen/tello_ros), a ROS2-Crystal / C++ driver for Tello from 2019, tested on Ubuntu 18.04, last updated Feb22. There seems to be several active forks.

Although I initially discarded them, they have interesting elements like swarm or SLAM capability, to explore in the future:

* https://github.com/LucaRitz/tello ROS2 / C++ 17 driver for Tello, implements Swarm. Tested in windows. Several dependencies. Last updated Oct20
* https://github.com/vss2sn/tello A C++ library for the Tello and Tello Edu. Features joystick control, command line control, command queues and SLAM. Last updated Sep20

# Tags
#tags: 

- [ ] basics
- [ ] algorithms
- [ ] data_structures: trees, graphs
- [ ] strings: regex
- [x] dates_times: timezones
- [ ] file_management: input, output, folders and files
- [ ] testing
- [ ] exceptions
- [ ] logging
- [x] object_oriented_programming
- [ ] GUI
- [ ] plotting_data
- [x] CLI
- [ ] arduino
- [ ] ROS
- [ ] AI_tools: chat GPT
- [ ] databases
- [ ] API
- [ ] web_scraping
- [x] Tello