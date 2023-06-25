#link: https://github.com/OneLoneCoder/olcPixelGameEngine

# Command Line Game Engine

My next challenge is to build a clone of the game Asteroids. 

I was planning on following [this tutorial by OneLoneCoder(@javidx9)](https://www.youtube.com/watch?v=QgDR8LrRZhk). However it makes use of the `olcConsoleGameEngine`](https://github.com/OneLoneCoder/Javidx9/tree/master/ConsoleGameEngine) which is Windows specific. 

`olcPixelGameEngine` however, by the same author, is cross-platform. So in thie project we will get it to work in preparation for a future project in which we will apply it to build Asteroids.

Repo: https://github.com/OneLoneCoder/olcPixelGameEngine/
Documentation: https://github.com/OneLoneCoder/olcPixelGameEngine/wiki

## Installation

* Download from the repo to our project folder the header file [olcPixelGameEngine.h](https://github.com/OneLoneCoder/olcPixelGameEngine/blob/master/olcPixelGameEngine.h)

* Install dependencies (cfr: https://github.com/OneLoneCoder/olcPixelGameEngine/wiki/Compiling-on-Linux)

```bash
$ sudo apt update
$ sudo apt install build-essential libglu1-mesa-dev libpng-dev
```
* To compile in vscode, add dependencies to `tasks.json`:

```json
"args": [
                "-std=c++17",
                ...
                "-lX11",
                "-lGL",
                "-lpthread",
                "-lpng",
                "-lstdc++fs",
                ...
]
```

## Usage

1. Include the header file `olcPixelGameEngine.h` from a source file
2. Derive a sub-class from `olc::PixelGameEngine`
3. Implement a constructor for your derived class, and name your application
4. Optionally override the `OnUserCreate()` function (initialization)
5. Override the `OnUserUpdate()` function (main loop)
6. Optionally override the `OnUserDestroy()` function (tear down)
7. Create an instance of your derived class somewhere, typically `main()`
8. Call the `Construct()` function and specify the screen and pixel dimensions
9. Call the `Start()` function to start the engine

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
- [ ] OpenCV