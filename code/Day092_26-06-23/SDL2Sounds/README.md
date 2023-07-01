#link: https://www.youtube.com/watch?v=lBCVC7ubBzs

# SDLSound

## Installing SDL in ubuntu
See https://wiki.libsdl.org/SDL2/Installation nd https://github.com/libsdl-org/SDL/blob/main/docs/README-linux.md

Dependencies:
```bash
$ sudo apt-get install build-essential git make \
pkg-config cmake ninja-build gnome-desktop-testing libasound2-dev libpulse-dev \
libaudio-dev libjack-dev libsndio-dev libx11-dev libxext-dev \
libxrandr-dev libxcursor-dev libxfixes-dev libxi-dev libxss-dev \
libxkbcommon-dev libdrm-dev libgbm-dev libgl1-mesa-dev libgles2-mesa-dev \
libegl1-mesa-dev libdbus-1-dev libibus-1.0-dev libudev-dev fcitx-libs-dev
```
Library:
```bash
$ sudo apt-get install libsdl2-dev
```

Compile with
```bash
$ gcc -o myprogram myprogram.c `sdl2-config --cflags --libs`
```
Or add in `tasks.json` : 
```json

"includePath": [
                ...                
                "`sdl2-config --cflags --libs`"
                ...
```

And add in `c_cpp_properties.json` : 
```json

"includePath": [
                ...                
                "/usr/include/SDL2/**"
                ...
```

## Getting it to work (not obvious)

I tried first this tutorial: https://moderncprogramming.com/programming-with-sdl-audio-in-pure-c-how-to-start/ (see `main.bak` file) and it does plays some scrambled sound but it is not right. I guess sampling rate or some other parameter was incorrect?

The example described in the video tutorial in the link above initially did nothing.

I then tried this one : https://www.youtube.com/watch?v=6IX6873J1Y8 and got it working, see `main3.bak`, and inferred that I was missing the call to `SDL_Init()` in the previous example.

So I finally got it to work! I wrapped SDL in a simple `Audio` class that allows playing simple WAV files to make sound effects! 

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
- [x] object_oriented_programming
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
- [x] sounds