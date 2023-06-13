#link: https://www.educative.io/blog/modern-multithreading-and-concurrency-in-cpp

# Threads 3

The tutorial in the link above contains an exercise that I used as inspiration for this third example.
- write a function that prints a vector of strings
- simulate a slow process by adding a `sleep_for()` function proportional to the length of the string to print
- without threading the strings print sequentially, it takes ~186ms 
- with threading all the print takes 39ms, the duration of the slowest thread, but print outs are not in order

```bash
1 : longer to print than a shorter one
2 : threads work in parallel
3 : can be faster than a sequence
4 : but without mutex
5 : the order is not guaranteed

Baseline (without threading) = 185723[µs]

4 : but without mutex
2 : threads work in parallel
5 : the order is not guaranteed
3 : can be faster than a sequence
0 : A very long sentence may take 
1 : longer to print than a shorter one

With threading = 39013[µs]
```

# Tags
#tags: 

- [x] threads
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
- [ ] OpenCV