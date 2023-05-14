#link: https://www.youtube.com/watch?v=A4UDOAOTRdw

# Multiple Object Tracking by Image Subtraction

This is Part 4 of the tutorial series [Car Counting C++](https://www.youtube.com/watch?v=Y3ac5rFMNZ0). It builds upon the code developed in Part 2 (project [Pedestrians](https://github.com/mhered/cpp_100daysofcode/blob/main/code/Day045_10-05-23/Pedestrians)) to detect movement by image subtraction, and the code developed for Part 3 (project [PredictMouseMove](https://github.com/mhered/cpp_100daysofcode/blob/main/code/Day046_11-05-23/PredictMouseMove)) to predict movement based on previous trayectory.

Note that the tutorial is based on OpenCV v3 and requires tuning some names of functions and constants.

Repo: https://github.com/MicrocontrollersAndMore/OpenCV_3_Multiple_Object_Tracking_by_Image_Subtraction_Cpp/blob/master/Blob.cpp

Practice on the sample file `768x576.avi` tracking multiple pedestrians walking around the scene. Label each pedestrian detected with a unique ID.

## To do
- [ ] Improve quality of detection. It struggles when people stop and when people cross each other. See paper: [Discrete-Continuous optimization for multi-target tracking](https://www.google.com/url?sa=t&rct=j&q=&esrc=s&source=web&cd=&ved=2ahUKEwjv1IjyrPX-AhVxQaQEHYDxB8QQFnoECAQQAQ&url=https%3A%2F%2Fethz.ch%2Fcontent%2Fdam%2Fethz%2Fspecial-interest%2Fbaug%2Figp%2Fphotogrammetry-remote-sensing-dam%2Fdocuments%2Fpdf%2Fcvpr2012-anton.pdf&usg=AOvVaw0JrXE4bj_5wUW9HYTZelFy) by Andriyenko, Schindler and Roth and companion video: https://www.youtube.com/watch?v=Z9X3IhHytrQ
- [ ] Part 5: OpenCV 3 Car Counting C++

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