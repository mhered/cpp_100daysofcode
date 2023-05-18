#link: https://github.com/herrnamenlos123/tello

# Tello

The ultimate goal is to replicate using C++ at least some of the projects I did two years ago with my Tello drone using python: https://github.com/mhered/tello-fun , then proceed to integrate it with ROS2:

* After looking around I decide to try out [tello](https://github.com/herrnamenlos123/tello), a C++14 single-header library to control the Tello, last updated in Nov22. Note it uses SDK 2.0, which apparently may be not fully compatible with the "normal" Tello. 

* For ROS2 integration, later down the road,  I am considering [tello_ros](https://github.com/clydemcqueen/tello_ros), a ROS2-Crystal / C++ driver for Tello from 2019, tested on Ubuntu 18.04, last updated Feb22. There seems to be several active forks.


## Getting started

1. Download `tello.hpp` from https://github.com/mcx/tello/tree/master on to the project folder
2. Download the example `main.cpp` from https://github.com/mcx/tello/tree/master/example/src/
3. Note: compiling failed with message `usr/include/c++/9/thread:126: undefined reference to 'pthread_create'`. I fixed it adding `"-lpthread"` to `"args":` in `tasks.json`, see here: https://stackoverflow.com/questions/1662909/undefined-reference-to-pthread-create-in-linux

Note: to connect the Tello drone to the laptop:
1. Switch on the Tello drone pressing the side button
2. Connect the laptop to `TELLO-EFD008` WIFI network and wait for a blinking yellow LED in the Tello drone

## The task

Implement a simple menu to launch 3 different basic demos:
* `void demo_fly()` - automatically take off, turn left and right and land, with suitable waits in between.
* `void demo_cam()` - switch on the Tello camera and stream video to the laptop, using OpenCV
* `void demo_key()` - implement basic control for the Tello with the laptop keyboard: take off, move up/down, rotate left/right and land. 

Even though I was not able to get the third demo working I call it a day: it is very late and I have exhausted three batteries. Tomorrow more!

## Other C++ Tello libraries

Although I initially discarded them, they have interesting elements like swarm or SLAM capability, to explore in the future:

* https://github.com/LucaRitz/tello ROS2 / C++ 17 driver for Tello, implements Swarm. Tested in windows. Several dependencies. Last updated Oct20
* https://github.com/vss2sn/tello A C++ library for the Tello and Tello Edu. Features joystick control, command line control, command queues and SLAM. Last updated Sep20

# Tags
#tags: 

- [ ] basics
- [ ] algorithms
- [ ] data_structures: trees, graphs
- [ ] strings: regex
- [ ] dates_times: timezones
- [ ] file_management: input, output, folders and files
- [ ] testing
- [ ] exceptions
- [ ] logging
- [ ] object_oriented_programming
- [ ] GUI
- [ ] plotting_data
- [ ] CLI
- [ ] arduino
- [ ] ROS
- [ ] chatGPT
- [ ] databases
- [ ] API
- [ ] web_scraping
- [x] OpenCV
- [x] Tello