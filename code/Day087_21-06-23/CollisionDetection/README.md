#link: https://www.jeffreythompson.org/collision-detection/

# Collision Detection

A couple of years back I completed the [Self-Driving Cars with Duckietown MOOC](https://www.edx.org/course/self-driving-cars-with-duckietown) and got stuck in [one of the exercises which proposed to write a collision checker](https://github.com/duckietown/mooc-exercises/tree/daffy/collision). It is time to get back to it. Note the original exercise used python and a lot of the course infrastructure.

The goal is to write `Segment`, `Circle` and `Rectangle` classes that allow to translate, rotate and draw shapes, move them around and detect collisions with other shapes. I will be based on the phenomenal online book by Jeffrey Thompson on Collision Detection (see linke above as well as the book repo (Javascript): https://github.com/jeffThompson/CollisionDetection

To adapt the Javascript code to C++ we will relay on OpenCV for the graphical stuff and will build on the following previous projects:
* [PredictMouseMove](https://github.com/mhered/cpp_100daysofcode/blob/main/code/Day046_11-05-23/PredictMouseMove) for capturing mouse movement.
* [Rectangle](https://github.com/mhered/cpp_100daysofcode/blob/main/code/Day083_17-06-23/Rectangle) for drawing and moving the rectangle

## Tasks
* create the write `Segment`, `Circle` and `Rectangle` classes including data members, constructors, as well as `collides_with()` methods.
* create a target shape e.g. a `Circle`
* create a second shape, which the user can move and rotate using the mouse, e.g. a `Rectangle`
* implement a loop that displays the shapes, checks for collision and notifies the user e.g. by changing the color in which the user shape is displayed.

## To Do

- [ ] Implement Rectangle - Rectangle collision
- [ ] OpenCV requires integer coordinates to display shapes, i.e. based on `cv::Point` not `cv::Point2d`. I settled for this loss of accuracy out of laziness but in reality all calculation should be made with `double` and generate `int` entities last minute and for display only.
- [ ] for some reason rotation only works when clicking + mouse move. Should not require mouse move...

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
- [ ] AI_tools: chat GPT
- [ ] databases
- [ ] API
- [ ] web_scraping
- [x] OpenCV