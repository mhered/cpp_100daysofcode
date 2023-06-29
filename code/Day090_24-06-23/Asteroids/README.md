#link: https://www.youtube.com/watch?v=QgDR8LrRZhk

# Asteroids

The challenge is to build a clone of the classic arcade game [Asteroids](https://en.wikipedia.org/wiki/Asteroids_(video_game)) by Atari following the excellent tutorial by OneLoneCoder(@javidx9) in the link above.

The original code was based on the `olcConsoleGameEngine` game engine written by OneLoneCoder(@javidx9), which is Windows-specific. In order to get it to work in Linux I had to modify the code a little bit to adapt it to `olc::PixelGameEngine`, a cross-platform game engine by the same author.

The exercise includes a demonstration of vector graphics, physics, wireframe graphics, 2D matrix transformations, toroidal space mapping and vector manipulation.

Note: `Asteroids.bak` tweaked from  [OneLoneCoder_Asteroids.cpp](https://github.com/OneLoneCoder/Javidx9/blob/master/ConsoleGameEngine/SmallerProjects/OneLoneCoder_Asteroids.cpp) to adapt it to `olc::PixelGameEngine`.
`main.cpp` written following the tutorial, with some aesthetical improvements:
* Enhanced looks for the space ship
* Display a plume when thrust is on
* Bullets have speed relative to the ship when firing
* Exploding asteroids have speed relative to the parent asteroid
* Different starting angle for each asteroids, different rotating speeds for each size asteroids for better looks
* 3 asteroids at the start of each level, out of the way

## To Do
- [ ] sound effects
- [ ] random shapes for each asteroid
- [ ] levels

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