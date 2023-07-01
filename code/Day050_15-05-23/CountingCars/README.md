#link: https://www.youtube.com/watch?v=Y3ac5rFMNZ0&t=0s

# Counting Cars
This is Part 5 and final of the tutorial series [Car Counting C++](https://www.youtube.com/watch?v=Y3ac5rFMNZ0). 

It builds upon the code developed in Part 2 (project [Pedestrians](https://github.com/mhered/cpp_100daysofcode/blob/main/code/Day045_10-05-23/Pedestrians)) to detect movement by image subtraction, the code developed for Part 3 (project [PredictMouseMove](https://github.com/mhered/cpp_100daysofcode/blob/main/code/Day046_11-05-23/PredictMouseMove)) to predict movement based on previous trayectory, and the code developed for Part 4 (project [MultipleObjectTracking](https://github.com/mhered/cpp_100daysofcode/blob/main/code/Day048_13-05-23/MultipleObjectTracking)) to track multiple moving objects.

Note that the tutorial is based on OpenCV v3 and requires tuning some names of functions and constants.

Repo: https://github.com/MicrocontrollersAndMore/OpenCV_3_Car_Counting_Cpp/tree/master

The idea of assigning an individual color to each car and drawing the last portion of the trayectory of the centre was taken from this example: https://www.youtube.com/watch?v=Z9X3IhHytrQ


Sample files (not committed):
* "CarsDrivingUnderBridge.mp4" original sample file from this repo: https://github.com/MicrocontrollersAndMore/OpenCV_3_Car_Counting_Cpp, works very well with crossing line at 35%
* "count_cars_2.mp4" - zoomed in version of previous video (does not work as well)
* "countingcars_input.mp4" - sample video from clips IMG_1832.MP4 - IMG_1843.MP$ recorded by me. Gives errors due to: different sizes of clips and transitions between them, cars moving close together at same speed in dense traffic, trucks, shadows, bird crossing field of view, trees moving from wind, crossing line too high... 
* "countingcars_input2.mp4" -zoomed in version of previous video, also does not work so well, same reasons
* "HSCCInterstateHighwaySurveillanceSystem-TESTVIDEO.mp4" original sample file from this repo: https://github.com/ahmetozlu/vehicle_counting/tree/master/src crossing line is too high -> works better at 45%, maybe need to detect smaller blobs. This sample also would allow counting traffic in both directions

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