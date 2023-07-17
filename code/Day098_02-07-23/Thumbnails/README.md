#link:

# Thumbnails

Create a function `Thumbnail()`:

```c++
bool Thumbnail(fs::path img_file_path,
               const fs::path tmb_folder_path,
               const int MAX_WIDTH = 200,
               const int MAX_HEIGHT = 200,
               bool verbose = false)`
```
The function receives:
- a path to an image or video file
- a path to the destination folder
- the maximum width and height dimensions of the thumbnails
- a `bool verbose` parameter 
  
The function will:
- create a thumbnail not larger than the designated maximum dimensions while respecting the original aspect ratio
- for video files of animated gifs the thumbnail will be created from a frame about 10% into the duration of the video
- save the thumbnail with the name `tmb_[STEM].jpg` to the destination folder 
- return `true` if successful, `false` otherwise
- prints out verbose output to facilitate debugging when `bool verbose = true`


# Tags
#tags: 

- [ ] basics
- [ ] algorithms
- [ ] data_structures: trees, graphs
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
- [x] OpenCV