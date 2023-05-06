#link: https://www.opencv-srf.com/p/opencv-lessons.html

# Exploring OpenCV 

## More on configuration

* adding `"``pkg-config --cflags --libs opencv4``"` folder to `args` in `tasks.json` allows compiling and executing as usual using the Run/Debug button, instead of the Makefile option
 
## Video and Image Processing
Create an app to practice image and video processing:
- Open a video from a file or webcam, apply image processing frame by frame and display the result in a window.
- Provide facilities to save a frame on demand

Examples of image processing:
- resizing
- annotation
- pixel-wise operations, e.g. change brightness or contrast
- filtering: Gaussian blur
- histogram equalization

## Notes

- Note that OpenCV does not know how fast to replay the video! Try this solution to wait for keypress to match processing time and frame rate: https://stackoverflow.com/a/21995693/15472802. This also fixed the problem that it used to work on saved videos but stall when fed live webcam input, even a scaled down one.
- Use this [ASCII table](https://www.asciitable.com/) to look out codes for `waitKey()` codes


- A good tutorial on face detection with OpenCV: https://www.youtube.com/watch?v=K_am9oMeweA

# Tags
#tags: Dig deeper in the OpenCV tutorials

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