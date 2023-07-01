#link: https://www.youtube.com/watch?v=5SzNuPSaISM

# Image Subtraction

Apply Image subtraction to detect multiple pedestrians walking around in the sample file `768x576.avi`
This is part 2 of the tutorial series [Car Counting C++](https://www.youtube.com/watch?v=Y3ac5rFMNZ0).

Repo: https://github.com/MicrocontrollersAndMore/OpenCV_3_Image_Subtraction_Cpp/tree/master

Note that the tutorial is based on OpenCV v3 and it may require tuning some names of functions and constants. Steps:
- preprocess 2 frames of the video
- subtract them and threshold the resulting difference
- find contours
- calculate blobs applying convex hulls
- filter the resulting blogs according to certain criteria (shape size) to adapt to the objcts you are looking for
- draw bounding rectangles and centers

Display a composite image of the 4 steps of the procesing (image subtraction, contours, blobs and the video annotated with rectangles and cntres)

## To do
Part 3: OpenCV 3 Mouse Move Prediction Algorithm C++
Part 4: OpenCV 3 Multiple Object Tracking by Image Subtraction C++ full source code
Part 5: OpenCV 3 Car Counting C++ full source code

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
- [ ] AI_tools: chat GPT
- [ ] databases
- [ ] API
- [ ] web_scraping
- [x] OpenCV