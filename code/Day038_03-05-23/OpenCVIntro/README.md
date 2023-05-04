#link: https://medium.com/analytics-vidhya/how-to-install-opencv-for-visual-studio-code-using-ubuntu-os-9398b2f32d53

# OpenCV Intro

## Install and configure

Install OpenCV and configure it to use with c++ in vscode following these instructions: https://medium.com/analytics-vidhya/how-to-install-opencv-for-visual-studio-code-using-ubuntu-os-9398b2f32d53

configuration entails:
* adding the include folder to the path in `c_cpp_properties.json`:

```json
"includePath":  [
    ...
    "/usr/include/opencv4/**",
    ...
    ],
```

* creating a Makefile:

```Makefile
CC = g++
PROJECT = bin/main
SRC = main.cpp
LIBS = `pkg-config --cflags --libs opencv4`
$(PROJECT) : $(SRC) 
	$(CC) $(SRC) -o $(PROJECT) $(LIBS)
```

To compile: `$ make` from inside the project folder
To execute: `./bin/main`

## Hello world!

Create a function that opens an image and displays it in a window. If called with an invalid filename it creates a 640x480 image of an empty background of color [Tomato](https://www.w3schools.com/colors/color_tryit.asp?color=Tomato): #FF6347 / rgb(255, 99, 71)

```bash
$ ./bin/main OpenCV.png "The OpenCV logo"
$ ./bin/main invalid.jpg
Could not open or find the image "invalid.jpg" I'll show you Tomato.
```
## To Do
- [ ] OpenCV in C++ Tutorials: https://www.opencv-srf.com/p/opencv-lessons.html

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