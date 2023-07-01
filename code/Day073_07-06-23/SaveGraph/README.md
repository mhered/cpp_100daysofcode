#link:

# PersistGraph

Develop a simple facility to read/write the information describing a graph to/from a plain text file

E.g. for this graph described by `NodeCoordinates` and `Adjacency`:
```
NodeCoordinates = {
        {15.0, 8.6603}, // Node 0
        {0.0, 0.0},     // Node 1
        {20.0, 0.0},    // Node 2
        {25.0, 8.6603}, // Node 3
        {10.0, 0.0},    // Node 4
        {5.0, 8.6603}}; // Node 5

    Adjacency = {
        {0, 0, 1, 1, 1, 1},  // Node 0
        {0, 0, 0, 0, 1, 1},  // Node 1
        {0, 0, 0, 1, 1, 0},  // Node 2
        {0, 0, 0, 0, 0, 0},  // Node 3
        {0, 0, 0, 0, 0, 1},  // Node 4
        {1, 0, 0, 0, 0, 0}}; // Node 5
```
The function `save_to_file("example1.graph", NodeCoordinates, Adjacency)` will write the following plain text file `example1.graph`:
```
6

15.0 8.6603
0.0 0.0
20.0 0.0
25.0 8.6603
10.0 0.0
5.0 8.6603

0 0 1 1 1 1
0 0 0 0 1 1
0 0 0 1 1 0
0 0 0 0 0 0
0 0 0 0 0 1
1 0 0 0 0 0
```
Similarly the function `read_from_file("example3.graph", NodeCoordinates, Adjacency)` will retrieve `NodeCoordinates` and `Adjacency` from the above file.


# Tags
#tags: 

- [ ] basics
- [ ] algorithms
- [x] data_structures: trees, graphs
- [ ] strings: regex
- [ ] dates_times: timezones
- [x] file_management: input, output, folders and files
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
- [ ] OpenCV