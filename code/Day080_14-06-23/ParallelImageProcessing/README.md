#link: https://solarianprogrammer.com/2011/12/16/cpp-11-thread-tutorial/

# Speeding up image processing with threads 

The tutorial in the link above describes a real-life application of threads to speed-up image processing.

The code does the following:
* Load an image to memory.
* Split the image in chunks to be processed by a number of threads corresponding to the max number of threads accepted by your system, e.g. on a quad-core computer we could use 8 threads.
* Launch number of threads - 1 (7 for a quad-core system), each one will process its chunk of the image.
* Let the main thread to deal with the last chunk of the image.
* Wait until all threads have finished and join them with the main thread.
* Save the processed image.

I downloaded a large sample image `sample_5184×3456.bmp` from here: https://filesamples.com/formats/bmp and post-processed in Gimp to 1) add noise to the left half and 2) export it in PPM format to `sample_5184×3456.ppm`  

The code in the tutorial refers to a custom class `ppm` that implements reading and writing PPM images as well as `bounds()` and `tst()` functions - respectively to define the image chunks and to actually apply the blur filter. 

I thought about rewriting it all using OpenCV but then again probably filters in OpenCV already apply threads and the comparison would not show improvements, so I decided to focus on the use of threads and downloaded all the auxiliary code from the tutorial repo: https://github.com/sol-prog/threads/tree/master/image_processing 

I tested launching different number of threads and as expected there is initially a trade off between the overhead of creating threads and the efficiencies of parallelization and later on an reduction in performance caused by switching when the number of threads if higher then the number of cores, see a detailed discussion here: https://www.baeldung.com/cs/servers-threads-number

Results:

```
Elapsed Time without threads: 1708550 microseconds
Elapsed Time with 2 threads: 1740216 microseconds
With vs without threads: -1.85338% less time with threads 
Elapsed Time with 3 threads: 889136 microseconds
With vs without threads: 47.9596% less time with threads 
Elapsed Time with 4 threads: 747558 microseconds
With vs without threads: 56.2461% less time with threads 
Elapsed Time with 6 threads: 728360 microseconds
With vs without threads: 57.3697% less time with threads 
Elapsed Time with 10 threads: 721156 microseconds
With vs without threads: 57.7913% less time with threads 
Elapsed Time with 16 threads: 719432 microseconds
With vs without threads: 57.8922% less time with threads 
Elapsed Time with 20 threads: 737341 microseconds
With vs without threads: 56.844% less time with threads 
Elapsed Time with 24 threads: 857312 microseconds
With vs without threads: 49.8222% less time with threads 
```

| Before blur | After blur |
| ------------------- | ----------------- |
| ![](./before_blur.jpg) | ![](./after_blur.jpg) |


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