#link: 

# Asteroids with Sound Effects OK

Let's combine project [Asteroids](https://github.com/mhered/cpp_100daysofcode/blob/main/code/Day090_24-06-23/Asteroids) and [SDL2Sounds](https://github.com/mhered/cpp_100daysofcode/blob/main/code/Day092_26-06-23/SDL2Sounds) and add sound effects to Asteroids!

## Configuration

To compile we need to add all dependencies in `tasks.json`:

```json
 "args": [
            ...
            "`sdl2-config --cflags --libs`",
            "-lX11",
            "-lGL",
            "-lpthread",
            "-lpng",
            "-lstdc++fs"
            ...
```

And make the SDL include folder accesible in `c_cpp_properties.json` : 
```json

"includePath": [
                ...                
                "/usr/include/SDL2/**"
                ...
```

For some reason this approach does not work: I couldn't manage to play any sounds, and  additionally the program crashes on exit.
Maybe I should play the sounds inside separate threads?

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
- [ ] OpenCV
- [x] games
- [x] sounds 