#link:

# Convert a BMP Map to a Graph

Lets imagine you receive a map of a terrain as a grayscale BMP image where each pixel represents a position in space, and its value represents the probability 0-255 of an obstacle in this position. The goal is to write code to read the image, and produce an undirected graph where each pixel is represented by a node. Nodes are connected to their neighbors in horizontal, vertical and diagonal directions provided they are valid positions (i.e. inside the map and free of obstacles). Add a weight to the edges calculated as the distance between neighboring pixels

Define parameters:
* RESOLUTION: 10mm/pixel
* THRESHOLD: consider a position free of obstacles if the intensity of the pixel in the map is >250


Default test image (The asterisks in *6* represent that there is an obstacle i nthis position):

```
 0  1  2  3
 4  5 *6* 7
 8  9 10 11
```
Expected result:
```
0 -> 1 4 5
1 -> 0 2 4 5
2 -> 1 3 5 7
3 -> 2 7
4 -> 0 1 5 8 9
5 -> 0 1 2 4 8 9 10
6 -> 
7 -> 2 3 10 11
8 -> 4 5 9
9 -> 4 5 8 10
10 -> 5 7 9 11
11 -> 7 10
```


##To do
- [x] make image for Day067
- [x] simplify graph plot because always bidirectional. (Done on Day068)
- [ ] refactor to make OOP

# Tags
#tags: 

- [ ] basics
- [ ] algorithms
- [x] data_structures: trees, graphs
- [ ] strings: regex
- [ ] dates_times: timezones
- [ ] file_management: input, output, folders and files
- [ ] testing
- [ ] exceptions
- [ ] logging
- [ ] object_oriented_programming
- [ ] GUI
- [x] plotting_data
- [ ] CLI
- [ ] arduino
- [ ] ROS
- [ ] chatGPT
- [ ] databases
- [ ] API
- [ ] web_scraping
- [x] OpenCV