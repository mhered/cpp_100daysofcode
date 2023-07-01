#link: https://github.com/alandefreitas/matplotplusplus/blob/master/examples/graphs/graph/graph_4.cpp

# Plot the Shortest Path

The ultimate goal is to build an animation of Dijkstra's algorithm similar to this one from Wikipedia:

![](https://upload.wikimedia.org/wikipedia/commons/2/23/Dijkstras_progress_animation.gif)

The link above shows an example of how to tune the format of each marker or edge separately using `matplot::graph`.

Lets start by plotting the final result, where node colors will represent distance to Target and the shortest path between Source and Target will be highlighted.

## To Do

I am starting to feel the weight of technical debt here. I barely managed to make it work on two of the ways of defining a graph (through node coordinates and adjacency matrix, or adding edges. Note in this second case it is necessary to manually add node coordinates even if weights will not necessarily be equal to the edge lengths).

- [ ] I really need to refactor and clean the code.
- [ ] I need yet more work to make it run on graphs created from bitmaps. Perhaps a simple facility to save and read graphs from file would be good.
- [ ] the implementation of edge weights in `matplot::graph` seems buggy. It does not work on `matplot::digraph`, or on vertical lines(!). Pending to plot two overlapping graphs: the full one and the one representing the shortest path. This would also simplify some of the awful code I wrote today... 

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
- [ ] OpenCV