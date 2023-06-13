#link: https://coderslegacy.com/cpp-multithreading-tutorial/

# Threads 1

I am curious about about concurrency and paralellism so I set out to learn about `std::thread`, `join()`, `std::mutex()` and the like:

- multithreading support was introduced in C++11
- need to include the library `<thread>`. 
- `std::thread` is the Class representing threads, which can be thought of as “virtual” cores, separate processing units that can execute tasks from your program independently from each other and at the same time.
- dependencies (precedence, shared data etc) complicate multithreading in practice
- The `join()` method can be thought of like this: creating threads splits up tasks to complete a project, but you need to `join()` them back together at the end. In practice `join()` forces the parent thread to wait for the completion of the child. 
-  the `isJoinable()` method returns `true` or `false`, depending on whether the thread is currently joinable or not.
- An alternative is the `separate()` method but you need to do what you are doing.

## Hello world

The most basic example is creating a thread and joining it.

## Resources
- A good first look: https://coderslegacy.com/cpp-multithreading-tutorial/
- Basics: https://www.educative.io/blog/modern-multithreading-and-concurrency-in-cpp
- A bit more extended including a subscriber-publisher example of practical use https://holowczak.com/introduction-to-multithreading-in-cplusplus/?amp=1
- A complete Stanford Course with chapters on threads, multithreading, parallelism, etc https://web.stanford.edu/class/cs110/

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